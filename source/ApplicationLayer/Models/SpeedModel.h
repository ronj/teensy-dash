#pragma once

// 8000 pulses/mile
// 1 mile = 1.609344 KM
// 8000 / 1.609344 = 4970.9695379
// 4971 pulses/KM

#include "Model.h"

namespace PeripheralLayer
{
	class Configuration;
	class PulseCounter;
}

namespace ApplicationLayer
{
	namespace Models
	{
		class SpeedModel : public Model
		{
		public:
			SpeedModel(const PeripheralLayer::Configuration& configuration, PeripheralLayer::PulseCounter& pulseCounter);

			virtual int32_t GetRawValue() const;
			virtual const char* GetFormattedValue() const;
			virtual void Update(uint32_t now);

		private:
			int32_t ConvertPulsesToSpeed(int32_t pulses, int32_t timediff) const;

		private:
			const uint16_t m_PulsesPerKm;
			uint16_t m_Speed;
			PeripheralLayer::PulseCounter& m_PulseCounter;
		};
	}
}
