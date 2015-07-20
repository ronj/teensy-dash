#include "FrequencyCounter.h"

#include "HardwareLayer/FrequencyCounter.h"

PeripheralLayer::FrequencyCounter::FrequencyCounter(HardwareLayer::FrequencyCounter& counter)
	: m_Counter(counter)
{
}

float PeripheralLayer::FrequencyCounter::GetFrequency()
{
	if (m_Counter.Available())
	{
		m_Sum += m_Counter.Read();
		m_Count++;

		if (m_Count > NUMBER_OF_ITERATIONS)
		{
			m_Frequency = m_Counter.CountToFrequency(m_Sum / m_Count);

			m_Sum = 0;
			m_Count = 0;
		}
	}
	else
	{
		m_Frequency = 0.f;
	}

	return m_Frequency;
}
