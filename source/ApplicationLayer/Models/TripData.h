#pragma once

#include "Common/List.h"

#include <cinttypes>

namespace ApplicationLayer
{
	namespace Models
	{
		class TripData : public Common::List<TripData>::Element
		{
		public:
			TripData() : Common::List<TripData>::Element(*this) {}

			void Update(uint32_t wheelTicks, uint32_t speed, uint32_t now);

			uint32_t GetTripWheelTicks() const;
			uint32_t GetTripTime() const;
			uint32_t GetTripMaxSpeed() const;

		private:
			uint32_t m_TripWheelTicks = 0;
			uint32_t m_TripTime = 0;
			uint32_t m_TripMaxSpeed = 0;
			uint32_t m_PreviousTime = 0;
		};
	}
}
