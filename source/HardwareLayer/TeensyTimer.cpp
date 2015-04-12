#include "TeensyTimer.h"

#include "WProgram.h"

uint32_t HardwareLayer::TeensyTimer::TickCountMilliseconds() const
{
	return millis();
}

uint32_t HardwareLayer::TeensyTimer::TickCountMicroseconds() const
{
	return micros();
}

void HardwareLayer::TeensyTimer::Sleep(uint32_t milliseconds) const
{
	delay(milliseconds);
}
