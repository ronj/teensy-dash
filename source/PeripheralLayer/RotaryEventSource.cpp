#include "RotaryEventSource.h"

#include "Common/Logger.h"

#include "HardwareLayer/DigitalPin.h"
#include "HardwareLayer/RotaryEncoder.h"

PeripheralLayer::RotaryEventSource::RotaryEventSource(HardwareLayer::RotaryEncoder& encoder, HardwareLayer::DigitalPin& button)
    : m_Encoder(encoder)
    , m_Button(button)
{
	m_Button.OnInterrupt = [this]() { m_ButtonPressed = true; };
	m_Button.EnableInterrupt(HardwareLayer::InterruptType::Rising);
}

bool PeripheralLayer::RotaryEventSource::EventAvailable()
{
	return m_Encoder.NewValueAvailable() || m_ButtonPressed;
}

PeripheralLayer::EventType PeripheralLayer::RotaryEventSource::Get()
{
	if (m_ButtonPressed)
	{
		m_ButtonPressed = false;
		return EventType::ShortPress;
	}

	switch (m_Encoder.GetDirection())
    {
        case 0x10 : return EventType::Next;
        case 0x20 : return EventType::Previous;
    }

    return EventType::None;
}
