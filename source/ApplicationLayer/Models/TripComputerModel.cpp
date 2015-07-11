#include "TripComputerModel.h"

#include "PeripheralLayer/Configuration.h"

#include "WheelTickModel.h"

#include "ConversionHelper.h"

ApplicationLayer::Models::TripComputerModel::TripComputerModel(const PeripheralLayer::Configuration& configuration, const WheelTickModel& wheelTicks)
	: m_WheelTicks(wheelTicks)
	, m_TicksToMeterFactor(configuration.GetVSSPulsesPerKm() / 1000.f)
{
	m_TripData.Add(m_TripA);
}

int32_t ApplicationLayer::Models::TripComputerModel::GetRawValue() const
{
	return TicksToDistance(m_TotalWheelTicks);
}

const char* ApplicationLayer::Models::TripComputerModel::GetFormattedValue() const
{
	static char formatted[8] = { 0 };

	itoa2(GetRawValue() / 1000, formatted, 10);

	return formatted;
}

void ApplicationLayer::Models::TripComputerModel::Update(uint32_t now)
{
	m_TotalWheelTicks += m_WheelTicks.GetRawValue();

	for (auto&& trip : m_TripData)
	{
		trip.Update(m_WheelTicks.GetRawValue(), 0, now);
	}
}

uint32_t ApplicationLayer::Models::TripComputerModel::TicksToDistance(uint64_t wheelTicks) const
{
	return static_cast<uint32_t>(wheelTicks / m_TicksToMeterFactor);
}
