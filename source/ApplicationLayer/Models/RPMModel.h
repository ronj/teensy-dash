#pragma once

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
		class RPMModel : public Model
		{
		public:
			RPMModel(const PeripheralLayer::Configuration& configuration, PeripheralLayer::PulseCounter& pulseCounter);

			virtual int32_t GetRawValue() const;
			virtual const char* GetFormattedValue() const;
			virtual void Update(uint32_t now);

		private:
			uint32_t ConvertPulsesToRPM(uint32_t pulses, uint32_t timediff) const;

		private:
			uint16_t m_RPM = 0;
			uint32_t m_PreviousTicks = 0;
			uint8_t m_PulsesPerRPM;
			PeripheralLayer::PulseCounter& m_PulseCounter;
		};
	}
}
