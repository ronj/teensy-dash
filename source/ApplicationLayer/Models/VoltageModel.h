#pragma once

#include "RepresentableModel.h"

namespace PeripheralLayer
{
	class Voltmeter;
}

namespace ApplicationLayer
{
	namespace Models
	{
		class VoltageModel : public RepresentableModel
		{
		public:
			VoltageModel(const PeripheralLayer::Voltmeter& meter);

			virtual int32_t GetRawValue() const;
			virtual const char* GetFormattedValue() const;
			virtual void Update(uint32_t);

		private:
			const PeripheralLayer::Voltmeter& m_Meter;
			int32_t m_Value;
		};
	}
}
