#include "RotaryEventSource.h"

#include "HardwareLayer/RotaryEncoder.h"

PeripheralLayer::RotaryEventSource::RotaryEventSource(HardwareLayer::RotaryEncoder& encoder)
    : m_Encoder(encoder)
{   
}

bool PeripheralLayer::RotaryEventSource::EventAvailable()
{
	return m_Encoder.NewValueAvailable();
}

PeripheralLayer::EventType PeripheralLayer::RotaryEventSource::Get()
{
	switch (m_Encoder.GetDirection())
    {
        case -1 : return EventType::Next;
        case  1 : return EventType::Previous;
    }

    return EventType::None;
}
