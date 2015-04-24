#include "PulseCounter.h"

#include "Common/DisableInterruptContext.h"

#include "HardwareLayer/DigitalPin.h"

#include <functional>

PeripheralLayer::PulseCounter::PulseCounter(HardwareLayer::DigitalPin& pin)
	: m_Pin(pin)
	, m_Counter(0)
{
	m_Pin.OnInterrupt = [this]() { ++m_Counter; };
	m_Pin.EnableInterrupt(HardwareLayer::InterruptType::Rising);
}

uint32_t PeripheralLayer::PulseCounter::GetCount()
{
	uint32_t count = 0;

	Common::DisableInterruptContext disableInterrupts;
	{
		count = m_Counter;
		m_Counter = 0;
	}

	return count;
}
