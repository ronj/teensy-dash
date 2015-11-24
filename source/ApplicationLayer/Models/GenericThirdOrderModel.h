#pragma once

#include "RepresentableModel.h"

#include <array>

namespace ApplicationLayer
{
	namespace Models
	{
		class GenericThirdOrderModel : public RepresentableModel
		{
		public:
			// Output = a x input^3 + b x input^2 + c x input + d
			GenericThirdOrderModel(float a, float b, float c, float d);

			virtual int32_t GetRawValue() const;
			virtual const char* GetFormattedValue() const;

			virtual void Update(uint32_t);

		private:
			std::array<float, 4> m_Poly;
			int32_t m_Value;
		};
	}
}
