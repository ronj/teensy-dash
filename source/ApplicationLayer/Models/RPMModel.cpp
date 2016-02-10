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

	snprintf(formatted, 5, "%d", ((GetRawValue() + 50) / 100) * 100);

	return formatted;
}

void ApplicationLayer::Models::RPMModel::Update(uint32_t)
{
	m_RPM = ConvertFrequencyToRPM(m_FrequencyCounter.GetFrequency());
}

uint32_t ApplicationLayer::Models::RPMModel::ConvertFrequencyToRPM(float frequency) const
{
	return static_cast<uint32_t>(((frequency) * 60.f)) / 2;
}
