#include "TripData.h"

#include <algorithm>

void ApplicationLayer::Models::TripData::Update(uint32_t wheelTicks, uint32_t speed, uint32_t now)
{
	if (wheelTicks > 0)
	{
		m_TripWheelTicks += wheelTicks;
		m_TripTime += (now - m_PreviousTime);
		m_TripMaxSpeed = std::max(speed, m_TripMaxSpeed);
	}

	m_PreviousTime = now;
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
