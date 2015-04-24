#include "TimeProvider.h"

#include "HardwareLayer/Timer.h"

PeripheralLayer::TimeProvider::TimeProvider(HardwareLayer::Timer& driver)
	: m_Timer(driver)
{
}

uint32_t PeripheralLayer::TimeProvider::TickCountMilliseconds()
{
	return m_Timer.TickCountMilliseconds();
}

uint32_t PeripheralLayer::TimeProvider::TickCountMicroseconds()
{
	return m_Timer.TickCountMicroseconds();
}

void PeripheralLayer::TimeProvider::Sleep(uint32_t milliseconds)
{
	m_Timer.Sleep(milliseconds);
}
