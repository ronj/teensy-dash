#include "CalculatedGearModel.h"

#include "ConversionHelper.h"

#include <cmath>

ApplicationLayer::Models::CalculatedGearModel::CalculatedGearModel(int tireWidth, int tireAspect, int rimSize, float finalDrive, Model& speedModel, Model& rpmModel)
	: m_Gear(0)
	, m_TireCircumfence(TireCircumfence(TireDiameter(tireWidth, tireAspect, rimSize)))
	, m_FinalDriveRatio(finalDrive)
	, m_SpeedModel(speedModel)
	, m_RpmModel(rpmModel)
{
	m_GearRatios[0] = 2.92f;
	m_GearRatios[1] = 1.87f;
	m_GearRatios[2] = 1.41f;
	m_GearRatios[3] = 1.15f;
	m_GearRatios[4] = 0.92f;
	m_GearRatios[5] = 0.79f;
}

int32_t ApplicationLayer::Models::CalculatedGearModel::GetRawValue() const
{
	return m_Gear;
}

const char* ApplicationLayer::Models::CalculatedGearModel::GetFormattedValue() const
{
	static char formatted[2] = { 0 };
	int32_t gear = GetRawValue();

	if (gear > 0)
	{
		itoa2(gear, formatted, 10);
	}
	else
	{
		formatted[0] = 'N';
	}

	return formatted;
}

void ApplicationLayer::Models::CalculatedGearModel::Update()
{
	m_Gear = DetermineGear(CalculateGearRatio(m_RpmModel.GetRawValue(), m_SpeedModel.GetRawValue()));
}

float ApplicationLayer::Models::CalculatedGearModel::CalculateGearRatio(int32_t rpm, int32_t speed) const
{
	float fractionalSpeed = (speed / 10) + ((speed % 10) / 10.f);
	return (60.f / 100000.f) * (rpm * m_TireCircumfence) / (fractionalSpeed * m_FinalDriveRatio);
}

uint8_t ApplicationLayer::Models::CalculatedGearModel::DetermineGear(float gearRatio)
{
	int32_t gear = 0;

	for (auto ratio : m_GearRatios)
	{
		if (std::isgreater(gearRatio, ratio))
		{
			return gear;
		}

		gear++;
	}

	return 0;
}
