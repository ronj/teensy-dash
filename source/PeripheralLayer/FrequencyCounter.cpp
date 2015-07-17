#include "FrequencyCounter.h"

#include "FreqMeasure.h"

PeripheralLayer::FrequencyCounter::FrequencyCounter()
{
	FreqMeasure.begin();
}

float PeripheralLayer::FrequencyCounter::GetFrequency()
{
	float frequency = 0.f;

	if (FreqMeasure.available())
	{
		m_Sum += FreqMeasure.read();
		m_Count++;

		if (m_Count > NUMBER_OF_ITERATIONS)
		{
			frequency = FreqMeasure.countToFrequency(m_Sum / m_Count);

			m_Sum = 0;
			m_Count = 0;
		}
	}

	return frequency;
}
