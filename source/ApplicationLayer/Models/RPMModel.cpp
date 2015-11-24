#include "RPMModel.h"

#include "ConversionHelper.h"

#include "PeripheralLayer/FrequencyCounter.h"

ApplicationLayer::Models::RPMModel::RPMModel(PeripheralLayer::FrequencyCounter& frequencyCounter)
	: m_FrequencyCounter(frequencyCounter)
{
}

int32_t ApplicationLayer::Models::RPMModel::GetRawValue() const
{
	return m_RPM;
}

const char* ApplicationLayer::Models::RPMModel::GetFormattedValue() const
{
	static char formatted[5] = { 0 };

	snprintf(formatted, 5, "%d", (GetRawValue() / 100) * 100);

	return formatted;
}

void ApplicationLayer::Models::RPMModel::Update(uint32_t now)
{
	m_RPM = ConvertFrequencyToRPM(m_FrequencyCounter.GetFrequency());
}

uint32_t ApplicationLayer::Models::RPMModel::ConvertFrequencyToRPM(float frequency) const
{
	// Why we read 1/3 too high is sill beyond me.
	// But in the absence of a logic analyser take if for granted
	// and introduce this fudge factor.
	return static_cast<uint32_t>(((frequency) * 60.f) * (2.f / 3.f));
}
