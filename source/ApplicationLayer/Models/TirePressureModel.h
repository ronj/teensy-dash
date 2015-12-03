#pragma once

#include "RepresentableModel.h"

namespace ApplicationLayer
{
	namespace Models
	{
		class TirePressureModel : public Model
		{
		public:
			TirePressureModel();

			virtual int32_t GetRawValue() const;
			virtual void Update(uint32_t);

			static void UnpackValues(int32_t input, uint16_t& frontLeft, uint16_t& frontRight, uint16_t& rearLeft, uint16_t& rearRight);

		private:
			uint32_t m_PackedValues = 0;
		};
	}
}
