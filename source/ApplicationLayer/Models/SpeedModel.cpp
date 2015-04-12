#include "SpeedModel.h"

#include "ConversionHelper.h"

ApplicationLayer::Models::SpeedModel::SpeedModel()
	: m_Speed(0)
{
}

int32_t ApplicationLayer::Models::SpeedModel::GetRawValue() const
{
	return m_Speed;
}

const char* ApplicationLayer::Models::SpeedModel::GetFormattedValue() const
{
	static char formatted[4] = { 0 };
	itoa2(GetRawValue() / 10, formatted, 10);
	return formatted;
}

void ApplicationLayer::Models::SpeedModel::Update()
{
	m_Speed = ConvertPulsesToSpeed(35, 1000);
}

int32_t ApplicationLayer::Models::SpeedModel::ConvertPulsesToSpeed(int32_t pulses, int32_t timediff) const
{
	return static_cast<int32_t>((pulses / (PulsesPerKM / (3.6f * timediff))) * 10);
}
