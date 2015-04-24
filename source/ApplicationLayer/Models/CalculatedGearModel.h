#pragma once

#include "Model.h"

#include <array>

namespace PeripheralLayer
{
	class Configuration;
}

namespace ApplicationLayer
{
	namespace Models
	{
		class CalculatedGearModel : public Model
		{
		public:
			CalculatedGearModel(const PeripheralLayer::Configuration& configuration, const Model& speedModel, const Model& rpmModel);

			virtual int32_t GetRawValue() const;
			virtual const char* GetFormattedValue() const;
			virtual void Update(uint32_t);

		private:
			float CalculateGearRatio(int32_t rpm, int32_t speed) const;
			uint8_t DetermineGear(float gearRatio) const;

			static float TireDiameter(int width, int aspect, int size);
			static float TireCircumfence(float rollingRadius);

		private:
			uint8_t m_Gear;
			float m_TireCircumfence;
			float m_FinalDriveRatio;
			const std::array<float, 6>& m_GearRatios;
			const Model& m_SpeedModel;
			const Model& m_RpmModel;
		};
	}
}
