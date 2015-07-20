#include "TripComputerModel.h"

#include "Common/Logger.h"

#include "PeripheralLayer/Configuration.h"

#include "WheelTickModel.h"

#include "ConversionHelper.h"

ApplicationLayer::Models::TripComputerModel::TripComputerModel(const PeripheralLayer::Configuration& configuration, const WheelTickModel& wheelTicks)
	: m_WheelTicks(wheelTicks)
	, m_TicksToMeterFactor(configuration.GetVSSPulsesPerKm() / 1000.f)
{
	m_TripDataList.Add(m_TripA);
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

	for (auto&& trip : m_TripDataList)
	{
		trip.Update(m_WheelTicks.GetRawValue(), 0, now);
	}
}

uint32_t ApplicationLayer::Models::TripComputerModel::GetTripDistance(uint8_t index) const
{
	return TicksToDistance(GetTrip(index).GetTripWheelTicks());
}

uint32_t ApplicationLayer::Models::TripComputerModel::GetTripTime(uint8_t index) const
{
	return GetTrip(index).GetTripTime();
}

const ApplicationLayer::Models::TripData& ApplicationLayer::Models::TripComputerModel::GetTrip(uint8_t index) const
{
	TripData* trip = m_TripDataList.GetFirst();

	for (int i = 0; i < index; i++)
	{
		trip = m_TripDataList.GetNext();
	}

	ASSERT_THAT(trip != nullptr);
	return *trip;
}

uint32_t ApplicationLayer::Models::TripComputerModel::TicksToDistance(uint64_t wheelTicks) const
{
	return static_cast<uint32_t>(wheelTicks / m_TicksToMeterFactor);
}
