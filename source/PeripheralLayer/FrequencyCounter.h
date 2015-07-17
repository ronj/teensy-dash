#pragma once

#include <cinttypes>

namespace HardwareLayer
{
}

namespace PeripheralLayer
{
	class FrequencyCounter
	{
	public:
		FrequencyCounter();

		virtual float GetFrequency();

	private:
		static const uint8_t NUMBER_OF_ITERATIONS = 1;
		uint8_t m_Count = 0;
		uint32_t m_Sum = 0;
	};
}
