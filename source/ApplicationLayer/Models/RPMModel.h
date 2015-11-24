#pragma once

#include "RepresentableModel.h"

namespace PeripheralLayer
{
	class FrequencyCounter;
}

namespace ApplicationLayer
{
	namespace Models
	{
		class RPMModel : public RepresentableModel
		{
		public:
			RPMModel(PeripheralLayer::FrequencyCounter& frequencyCounter);

			virtual int32_t GetRawValue() const;
			virtual const char* GetFormattedValue() const;
			virtual void Update(uint32_t);

		private:
			uint32_t ConvertFrequencyToRPM(float frequency) const;

		private:
			uint16_t m_RPM = 0;
			PeripheralLayer::FrequencyCounter& m_FrequencyCounter;
		};
	}
}
