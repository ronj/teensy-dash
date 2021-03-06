#pragma once

#include "RepresentableModel.h"
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
		class InjectorModel;

		class TripComputerModel : public RepresentableModel
		{
		public:
			TripComputerModel(const PeripheralLayer::Configuration& configuration, const WheelTickModel& wheelTicks, const InjectorModel& injectorDuration);

			virtual int32_t GetRawValue() const;
			virtual const char* GetFormattedValue() const;
			virtual void Update(uint32_t now);

			uint32_t GetTripDistance(uint8_t index) const;
			uint32_t GetTripTime(uint8_t index) const;
			uint32_t GetTripAverageSpeed(uint8_t index) const;
			uint32_t GetTripMaxSpeed(uint8_t index) const;
			uint32_t GetTripAverageFuelConsumption(uint8_t index) const;

		private:
			const TripData& GetTrip(uint8_t index) const;
			uint32_t TicksToDistance(uint64_t wheelTicks) const;

		private:
			const WheelTickModel& m_WheelTicks;
			const InjectorModel& m_InjectorDuration;

			TripData m_TripA;
			TripData m_TripB;
			TripData m_TripC;

			mutable Common::List<TripData> m_TripDataList;

			uint64_t m_TotalWheelTicks = 0;
			float m_TicksToMeterFactor = 0.f;
			uint32_t m_MicrosecondsPerLiter = 0;
		};
	}
}
