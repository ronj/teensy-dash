#include "SerialEventSource.h"

#include "Common/ArduinoWrapper.h"

bool PeripheralLayer::SerialEventSource::EventAvailable()
{
	return Serial.available() > 0;
}

PeripheralLayer::EventType PeripheralLayer::SerialEventSource::Get()
{
	if (Serial.available() > 0)
	{
		switch (Serial.read())
	    {
	        case '+' : return EventType::Next;
	        case '-' : return EventType::Previous;
	        case 'Q' : return EventType::Quit;
	    }
	}

    return EventType::None;
}
