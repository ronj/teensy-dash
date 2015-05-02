#include "RPMModel.h"

#include "ConversionHelper.h"

#include "PeripheralLayer/PulseCounter.h"

ApplicationLayer::Models::RPMModel::RPMModel(PeripheralLayer::PulseCounter& pulseCounter)
	: m_PulseCounter(pulseCounter)
{
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
	if (now - m_PreviousTicks >= 1000)
	{
		m_RPM = ConvertPulsesToRPM(m_PulseCounter.GetCount(), now - m_PreviousTicks);
		m_PreviousTicks = now;
	}
}

uint32_t ApplicationLayer::Models::RPMModel::ConvertPulsesToRPM(uint32_t pulses, uint32_t timediff) const
{
	return pulses * (60.0f / (timediff / 1000.0f));
}
