#pragma once

#include <cinttypes>

namespace HardwareLayer
{
	class FrequencyCounter;
}

namespace PeripheralLayer
{
	class FrequencyCounter
	{
	public:
		FrequencyCounter(HardwareLayer::FrequencyCounter& counter);

		virtual float GetFrequency();

	private:
		static const uint8_t NUMBER_OF_ITERATIONS = 1;

		HardwareLayer::FrequencyCounter& m_Counter;
		uint8_t m_Count = 0;
		uint32_t m_Sum = 0;
		float m_Frequency = 0.f;
	};
}
