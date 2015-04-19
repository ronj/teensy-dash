#include "SpeedModel.h"

#include "ConversionHelper.h"

#include "PeripheralLayer/Configuration.h"
#include "PeripheralLayer/PulseCounter.h"

ApplicationLayer::Models::SpeedModel::SpeedModel(const PeripheralLayer::Configuration& configuration, PeripheralLayer::PulseCounter& pulseCounter)
	: m_PulsesPerKm(configuration.GetVSSPulsesPerKm())
	, m_Speed(0)
	, m_PulseCounter(pulseCounter)
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

void ApplicationLayer::Models::SpeedModel::Update(uint32_t now)
{
	static unsigned long previous = 0;

	if (now - previous > 1000)
	{
		m_Speed = ConvertPulsesToSpeed(m_PulseCounter.GetCount(), now - previous);
		previous = now;
	}
}

int32_t ApplicationLayer::Models::SpeedModel::ConvertPulsesToSpeed(int32_t pulses, int32_t timediff) const
{
	return static_cast<int32_t>(((float)pulses / ((float)m_PulsesPerKm / (float)(3.6f * timediff))) * 10);
}
