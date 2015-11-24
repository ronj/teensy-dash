#pragma once

#include "Model.h"

namespace PeripheralLayer
{
	class PulseCounter;
}

namespace ApplicationLayer
{
	namespace Models
	{
		class WheelTickModel : public Model
		{
		public:
			WheelTickModel(PeripheralLayer::PulseCounter& pulseCounter);

			virtual int32_t GetRawValue() const;
			virtual void Update(uint32_t);

		private:
			PeripheralLayer::PulseCounter& m_PulseCounter;

			uint32_t m_CurrentWheelTicks = 0;
		};
	}
}
