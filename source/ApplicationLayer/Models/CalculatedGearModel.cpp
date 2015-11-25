#include "CalculatedGearModel.h"

#include "ConversionHelper.h"

#include "PeripheralLayer/Configuration.h"

#include "Common/Math.h"

#include <cmath>

ApplicationLayer::Models::CalculatedGearModel::CalculatedGearModel(const PeripheralLayer::Configuration& configuration, const Model& speedModel, const Model& rpmModel)
	: m_Gear(0)
	, m_TireCircumfence(TireCircumfence(TireDiameter(configuration.GetTireWidth(), configuration.GetTireAspect(), configuration.GetRimSize())))
	, m_FinalDriveRatio(configuration.GetFinalDriveRatio())
	, m_GearRatios(configuration.GetGearRatios())
	, m_SpeedModel(speedModel)
	, m_RpmModel(rpmModel)
{
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
		gear > 0 ? snprintf(formatted, 2, "%d", gear) :
			       snprintf(formatted, 2, "%s", "N");
	}
	else
	{
		formatted[0] = 'N';
	}

	return formatted;
}

void ApplicationLayer::Models::CalculatedGearModel::Update(uint32_t)
{
	m_Gear = DetermineGear(CalculateGearRatio(m_RpmModel.GetRawValue(), m_SpeedModel.GetRawValue()));
}

float ApplicationLayer::Models::CalculatedGearModel::CalculateGearRatio(int32_t rpm, int32_t speed) const
{
	if ((rpm == 0) || (speed == 0)) return 0.f;

	float fractionalSpeed = (speed / 10) + ((speed % 10) / 10.f);
	return (60.f / 100000.f) * (rpm * m_TireCircumfence) / (fractionalSpeed * m_FinalDriveRatio);
}

uint8_t ApplicationLayer::Models::CalculatedGearModel::DetermineGear(float gearRatio) const
{
	int32_t gear = 1;

	for (auto ratio : m_GearRatios)
	{
		if (std::isnan(ratio)) break;
		if (std::isgreater(gearRatio, ratio)) return gear;

		gear++;
	}

	return 0;
}

float ApplicationLayer::Models::CalculatedGearModel::TireDiameter(int width, int aspect, int size)
{
	return (size * 2.54f) + (((width / 10.f) * (aspect / 100.f)) * 2);
}

float ApplicationLayer::Models::CalculatedGearModel::TireCircumfence(float rollingRadius)
{
	return Common::Math::PI<float> * rollingRadius;
}
