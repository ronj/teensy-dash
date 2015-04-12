#pragma once

#include "Model.h"

namespace ApplicationLayer
{
	namespace Models
	{
		class CalculatedGearModel : public Model
		{
		public:
			CalculatedGearModel(int tireWidth, int tireAspect, int rimSize, float finalDrive, Model& speedModel, Model& rpmModel);

			virtual int32_t GetRawValue() const;
			virtual const char* GetFormattedValue() const;
			virtual void Update();

		private:
			float CalculateGearRatio(int32_t rpm, int32_t speed) const;
			uint8_t DetermineGear(float gearRatio);

			static float TireDiameter(int width, int aspect, int size)
			{
				return (size * 2.54f) + (((width / 10.0f) * (aspect / 100.0f)) * 2);
			}

			static float TireCircumfence(float rollingRadius)
			{
				return 3.14159f * rollingRadius;
			}

		private:
			uint8_t m_Gear;
			float m_TireCircumfence;
			float m_FinalDriveRatio;
			float m_GearRatios[6];
			Model& m_SpeedModel;
			Model& m_RpmModel;
		};
	}
}
