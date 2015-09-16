#pragma once

#include "Model.h"

namespace PeripheralLayer
{
	class PulseDuration;
}

namespace ApplicationLayer
{
	namespace Models
	{
		class InjectorModel : public Model
		{
		public:
			InjectorModel(PeripheralLayer::PulseDuration& pulseDuration);

			virtual int32_t GetRawValue() const;
			virtual void Update(uint32_t);

		private:
			// This is a "special" Model in the sense that it should
			// only be used by other Models, not directly by a view.
			virtual const char* GetFormattedValue() const;

		private:
			PeripheralLayer::PulseDuration& m_PulseDuration;

			uint32_t m_InjectorOpen = 0;
		};
	}
}
