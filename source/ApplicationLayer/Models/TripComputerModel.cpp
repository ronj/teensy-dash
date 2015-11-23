#include "TripComputerModel.h"

#include "Common/Logger.h"

#include "PeripheralLayer/Configuration.h"

#include "WheelTickModel.h"
#include "InjectorModel.h"

#include "ConversionHelper.h"

ApplicationLayer::Models::TripComputerModel::TripComputerModel(const PeripheralLayer::Configuration& configuration, const WheelTickModel& wheelTicks, const InjectorModel& injectorDuration)
	: m_WheelTicks(wheelTicks)
	, m_InjectorDuration(injectorDuration)
	, m_TicksToMeterFactor(configuration.GetVSSPulsesPerKm() / 1000.f)
	, m_MicrosecondsPerLiter(configuration.GetMicrosecondsPerLiter())
{
	m_TripDataList.Add(m_TripA);
	m_TripDataList.Add(m_TripB);
	m_TripDataList.Add(m_TripC);
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
		trip.Update(m_WheelTicks.GetRawValue(), 0, m_InjectorDuration.GetRawValue(), now);
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

uint32_t ApplicationLayer::Models::TripComputerModel::GetTripAverageSpeed(uint8_t index) const
{
	uint32_t timeMilliSeconds = GetTripTime(index);
	uint32_t distanceMeter = GetTripDistance(index);

	float timeHours = timeMilliSeconds / 1000.f / 60.f / 60.f;
	float distanceKilometer = distanceMeter / 1000.f;

	return static_cast<uint32_t>(distanceKilometer / timeHours);
}

uint32_t ApplicationLayer::Models::TripComputerModel::GetTripMaxSpeed(uint8_t index) const
{
	return GetTrip(index).GetTripMaxSpeed();
}

uint32_t ApplicationLayer::Models::TripComputerModel::GetTripAverageFuelConsumption(uint8_t index) const
{
	uint64_t injectorOpenMicroseconds = GetTrip(index).GetTripInjectorOpenDuration();
	uint32_t distanceMeter = GetTripDistance(index);

	float liters = injectorOpenMicroseconds / static_cast<float>(m_MicrosecondsPerLiter);
	float distanceKilometer = distanceMeter / 1000.f;

	return static_cast<uint32_t>((liters / distanceKilometer) * 100.f);
}

const ApplicationLayer::Models::TripData& ApplicationLayer::Models::TripComputerModel::GetTrip(uint8_t index) const
{
	ASSERT_THAT(!m_TripDataList.IsEmpty());

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
