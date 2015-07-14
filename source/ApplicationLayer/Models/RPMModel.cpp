#include "RPMModel.h"

#include "ConversionHelper.h"

#include "PeripheralLayer/PulseCounter.h"

//#include "FreqMeasure.h"

ApplicationLayer::Models::RPMModel::RPMModel(PeripheralLayer::PulseCounter& pulseCounter)
	: m_PulseCounter(pulseCounter)
{
	//FreqMeasure.begin();
}

int32_t ApplicationLayer::Models::RPMModel::GetRawValue() const
{
	return m_RPM;
}

const char* ApplicationLayer::Models::RPMModel::GetFormattedValue() const
{
	static char formatted[4] = { 0 };
	itoa2(GetRawValue(), formatted, 10);
	return formatted;
}

void ApplicationLayer::Models::RPMModel::Update(uint32_t now)
{
	static int count = 0;
	static double sum = 0;

	/*if (FreqMeasure.available())
	{
		sum += FreqMeasure.read();
		count += 1;

		if (count > 1)
		{
			float frequency = FreqMeasure.countToFrequency(sum / count);
			// Why we read 1/3 too high is sill beyond me.
			// But in the absence of a logic analyser take if for granted
			// and introduce this fudge factor.
			m_RPM = ((frequency) * 60.0f) * (2.f / 3.f);
			sum = 0;
			count = 0;
		}
	}
	else
	{
		m_RPM = 0;
	}*/
}

uint32_t ApplicationLayer::Models::RPMModel::ConvertPulsesToRPM(uint32_t pulses, uint32_t timediff) const
{
	return static_cast<uint32_t>(pulses * (60.0f / (timediff / 1000.0f)));
}
