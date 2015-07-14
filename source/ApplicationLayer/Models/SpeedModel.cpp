#include "SpeedModel.h"

#include "ConversionHelper.h"
#include "WheelTickModel.h"

#include "PeripheralLayer/Configuration.h"

ApplicationLayer::Models::SpeedModel::SpeedModel(const PeripheralLayer::Configuration& configuration, WheelTickModel& wheelTicks)
	: m_WheelTicks(wheelTicks)
	, m_PulseFactor(configuration.GetVSSPulsesPerKm() / 3600000.f)
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
	m_AccumulatedTicks += m_WheelTicks.GetRawValue();

	if (now - m_PreviousTickTime >= UPDATE_INTERVAL)
	{
		m_Speed = ConvertPulsesToSpeed(m_AccumulatedTicks, now - m_PreviousTickTime);
		m_PreviousTickTime = now;
		m_AccumulatedTicks = 0;
	}
}

uint32_t ApplicationLayer::Models::SpeedModel::ConvertPulsesToSpeed(uint32_t pulses, uint32_t timediff) const
{
	return static_cast<uint32_t>((pulses / (m_PulseFactor * timediff)) * 10);
}
