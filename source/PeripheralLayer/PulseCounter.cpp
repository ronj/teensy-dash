#include "PulseCounter.h"

#include "Common/DisableInterruptContext.h"

#include "HardwareLayer/DigitalPin.h"

PeripheralLayer::PulseCounter::PulseCounter(HardwareLayer::DigitalPin& pin)
	: m_Counter(0)
{
	pin.OnInterrupt = [this]() { ++m_Counter; };
	pin.EnableInterrupt(HardwareLayer::InterruptType::Rising);
}

uint32_t PeripheralLayer::PulseCounter::GetCount()
{
	uint32_t count = 0;
	{
		Common::DisableInterruptContext disableInterrupts;
		count = m_Counter;
		m_Counter = 0;
	}

	return count;
}
