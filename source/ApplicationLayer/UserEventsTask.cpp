#include "UserEventsTask.h"

#include "Common/ArduinoWrapper.h"
#include "Common/Math.h"
#include "Common/Logger.h"

ApplicationLayer::UserEventsTask::UserEventsTask()
	: m_CurrentEncoderValue(0)
	, m_PreviousEncoderValue(0)
	, m_Encoder(3, 4)
{
}

bool ApplicationLayer::UserEventsTask::CanRun(uint32_t)
{
	m_CurrentEncoderValue = m_Encoder.read();
	return (m_CurrentEncoderValue != m_PreviousEncoderValue) || Serial.available() > 0;
}

void ApplicationLayer::UserEventsTask::Run(uint32_t)
{
    int8_t direction = 0;

    if (Serial.available() > 0)
    {
      uint8_t command = Serial.read();
      if (command == 'N') direction = -1;
      else if (command == 'P') direction = 1;
    }
    else if (m_CurrentEncoderValue % 4 == 0)
    {
      m_Encoder.write(0);
      direction = Common::Math::Sign(m_CurrentEncoderValue);
    }

    if (direction == 1) CallOnPrevious();
    else if (direction == -1) CallOnNext();

    m_PreviousEncoderValue = m_CurrentEncoderValue;
}

void ApplicationLayer::UserEventsTask::CallOnPrevious()
{
	if (OnPrevious) OnPrevious();
}

void ApplicationLayer::UserEventsTask::CallOnNext()
{
	if (OnNext) OnNext();
}
