#pragma once

#include <cinttypes>

namespace HardwareLayer
{
	class DigitalPin;
}

namespace PeripheralLayer
{
	class PulseCounter
	{
	public:
		PulseCounter(HardwareLayer::DigitalPin& pin);

		virtual uint32_t GetCount();

	private:
		volatile unsigned long m_Counter;
	};
}
