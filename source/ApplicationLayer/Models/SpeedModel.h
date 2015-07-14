#pragma once

#include "Model.h"

namespace PeripheralLayer
{
	class Configuration;
}

namespace ApplicationLayer
{
	namespace Models
	{
		class WheelTickModel;

		class SpeedModel : public Model
		{
		public:
			SpeedModel(const PeripheralLayer::Configuration& configuration, WheelTickModel& wheelTicks);

			virtual int32_t GetRawValue() const;
			virtual const char* GetFormattedValue() const;
			virtual void Update(uint32_t now);

		private:
			uint32_t ConvertPulsesToSpeed(uint32_t pulses, uint32_t timediff) const;

		public:
			static const uint16_t UPDATE_INTERVAL = 500;

		private:
			WheelTickModel& m_WheelTicks;

			float m_PulseFactor = 0.f;
			uint32_t m_Speed = 0;
			uint32_t m_PreviousTickTime = 0;
			uint32_t m_AccumulatedTicks = 0;
		};
	}
}
