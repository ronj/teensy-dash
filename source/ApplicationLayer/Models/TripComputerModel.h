#pragma once

#include "Model.h"
#include "TripData.h"

#include "Common/List.h"

namespace PeripheralLayer
{
	class Configuration;
}

namespace ApplicationLayer
{
	namespace Models
	{
		class WheelTickModel;

		class TripComputerModel : public Model
		{
		public:
			TripComputerModel(const PeripheralLayer::Configuration& configuration, const WheelTickModel& wheelTicks);

			virtual int32_t GetRawValue() const;
			virtual const char* GetFormattedValue() const;
			virtual void Update(uint32_t now);

		private:
			uint32_t TicksToDistance(uint64_t wheelTicks) const;

		private:
			const WheelTickModel& m_WheelTicks;

			TripData m_TripA;
			Common::List<TripData> m_TripData;

			uint64_t m_TotalWheelTicks = 0;
			float m_TicksToMeterFactor = 0.f;
		};
	}
}
