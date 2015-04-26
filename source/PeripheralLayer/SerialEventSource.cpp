#include "SerialEventSource.h"

#include "Common/ArduinoWrapper.h"

bool PeripheralLayer::SerialEventSource::EventAvailable()
{
#ifndef BUILD_FOR_EMULATOR
	return Serial.available() > 0;
#else
	return false;
#endif
}

PeripheralLayer::EventType PeripheralLayer::SerialEventSource::Get()
{
#ifndef BUILD_FOR_EMULATOR
	if (Serial.available() > 0)
	{
		switch (Serial.read())
	    {
	        case '+' : return EventType::Next;
	        case '-' : return EventType::Previous;
	        case 'Q' : return EventType::Quit;
	    }
	}
#endif

    return EventType::None;
}
