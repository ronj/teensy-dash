#pragma once

#include "Model.h"

namespace PeripheralLayer
{
	class Configuration;
	class PulseDuration;
}

namespace ApplicationLayer
{
	namespace Models
	{
		class InjectorModel : public Model
		{
		public:
			InjectorModel(PeripheralLayer::PulseDuration& pulseDuration, const PeripheralLayer::Configuration& configuration);

			virtual int32_t GetRawValue() const;
			virtual void Update(uint32_t);

		private:
			const PeripheralLayer::Configuration& m_Configuration;
			PeripheralLayer::PulseDuration& m_PulseDuration;

			uint32_t m_InjectorOpen = 0;
		};
	}
}
