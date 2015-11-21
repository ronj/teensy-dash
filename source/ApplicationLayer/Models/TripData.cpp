#include "TripData.h"

#include <algorithm>

void ApplicationLayer::Models::TripData::Update(uint32_t wheelTicks, uint32_t speed, uint32_t injectorDuration, uint32_t now)
{
	if (wheelTicks > 0)
	{
		m_TripWheelTicks += wheelTicks;
		m_TripTime += (now - m_PreviousTime);
		m_TripMaxSpeed = std::max(speed, m_TripMaxSpeed);
		m_TripInjectorOpenDuration += injectorDuration;
	}
	else
	{
		m_TripIdleTime += (now - m_PreviousTime);
	}

	m_PreviousTime = now;
}

void ApplicationLayer::Models::TripData::Reset()
{
	m_TripWheelTicks = 0;
	m_TripTime = 0;
	m_TripMaxSpeed = 0;
}

uint32_t ApplicationLayer::Models::TripData::GetTripWheelTicks() const
{
	return m_TripWheelTicks;
}

uint32_t ApplicationLayer::Models::TripData::GetTripTime() const
{
	return m_TripTime;
}

uint32_t ApplicationLayer::Models::TripData::GetTripMaxSpeed() const
{
	return m_TripMaxSpeed;
}

uint64_t ApplicationLayer::Models::TripData::GetTripInjectorOpenDuration() const
{
	return m_TripInjectorOpenDuration;
}
