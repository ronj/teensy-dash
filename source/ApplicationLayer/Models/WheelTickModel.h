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
			// This is a "special" Model in the sense that it should
			// only be used by other Models, not directly by a view.
			virtual const char* GetFormattedValue() const;

		private:
			PeripheralLayer::PulseCounter& m_PulseCounter;

			uint32_t m_CurrentWheelTicks = 0;
		};
	}
}
