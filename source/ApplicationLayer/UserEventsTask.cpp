#include "UserEventsTask.h"

int sign(int value)
{ 
	return (value > 0) - (value < 0); 
}

ApplicationLayer::UserEventsTask::UserEventsTask()
	: m_CurrentEncoderValue(0)
	, m_PreviousEncoderValue(0)
	, m_Encoder(3, 4)
{
}

bool ApplicationLayer::UserEventsTask::CanRun(uint32_t)
{
	m_CurrentEncoderValue = m_Encoder.read();
	return m_CurrentEncoderValue != m_PreviousEncoderValue;
}

void ApplicationLayer::UserEventsTask::Run(uint32_t)
{
    if (m_CurrentEncoderValue % 4 == 0)
    {
      m_Encoder.write(0);

      int8_t direction = sign(m_CurrentEncoderValue);
      if (direction == 1) CallOnPrevious();
      if (direction == -1) CallOnNext();
    }

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
