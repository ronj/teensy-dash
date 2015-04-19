#include "PulseCounter.h"

#include "Common/ArduinoWrapper.h"
#include "Common/DisableInterruptContext.h"

static volatile unsigned long counter = 0;

void isrCounter()
{
	++counter;
}

PeripheralLayer::PulseCounter::PulseCounter()
{
	pinMode(23, INPUT);
	attachInterrupt(23, isrCounter, RISING);
}

uint32_t PeripheralLayer::PulseCounter::GetCount()
{
	uint32_t count = 0;

	Common::DisableInterruptContext disableInterrupts;
	{
		count = counter;
		counter = 0;
	}

	return count;
}
