#pragma once

#include "RepresentableModel.h"

namespace PeripheralLayer
{
	class ParkDistanceDecoder;
}

namespace ApplicationLayer
{
	namespace Models
	{
		class ParkDistanceModel : public RepresentableModel
		{
		public:
			ParkDistanceModel(const PeripheralLayer::ParkDistanceDecoder& parkDistanceDecoder);

			virtual int32_t GetRawValue() const;
			virtual const char* GetFormattedValue() const;
			virtual void Update(uint32_t);

			static void UnpackValues(int32_t input, uint8_t& sensorA, uint8_t& sensorB, uint8_t& sensorC, uint8_t& sensorD);

		private:
			const PeripheralLayer::ParkDistanceDecoder& m_ParkDistanceDecoder;

			uint32_t m_PackedValues = 0;
		};
	}
}
