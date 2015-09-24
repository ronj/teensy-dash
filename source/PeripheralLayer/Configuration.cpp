#include "Configuration.h"

#include <cmath>
#include <limits>

PeripheralLayer::Configuration::Configuration()
	: m_AccelerometerXCalibration(403, 604)
	, m_AccelerometerYCalibration(401, 599)
	, m_AccelerometerZCalibration(398, 608)
	, m_TireWidth(205)
	, m_TireAspect(40)
	, m_RimSize(17)
	, m_FinalDrive(59.f / 13.f)
	, m_GearRatios({ { 41.f / 12.f, 38.f / 21.f, 37.f / 29.f, 39.f / 40.f, 33.f / 43.f, UnavailableGear() } })
	, m_VSSPulsesPerKm(4971)
	, m_InjectorFlow(1493)
	, m_InjectorCount(4)
	, m_InjectorMechanicalDelay(50)
	, m_FuelPressure(3000)
{
}

const PeripheralLayer::Configuration::MinMaxCalibration<int16_t>& PeripheralLayer::Configuration::GetAccelerometerXCalibration() const
{
	return m_AccelerometerXCalibration;
}

const PeripheralLayer::Configuration::MinMaxCalibration<int16_t>& PeripheralLayer::Configuration::GetAccelerometerYCalibration() const
{
	return m_AccelerometerYCalibration;
}

const PeripheralLayer::Configuration::MinMaxCalibration<int16_t>& PeripheralLayer::Configuration::GetAccelerometerZCalibration() const
{
	return m_AccelerometerZCalibration;
}

uint16_t PeripheralLayer::Configuration::GetTireWidth() const
{
	return m_TireWidth;
}

uint8_t PeripheralLayer::Configuration::GetTireAspect() const
{
	return m_TireAspect;
}

uint8_t PeripheralLayer::Configuration::GetRimSize() const
{
	return m_RimSize;
}

float PeripheralLayer::Configuration::GetFinalDriveRatio() const
{
	return m_FinalDrive;
}

const std::array<float, 6>& PeripheralLayer::Configuration::GetGearRatios() const
{
	return m_GearRatios;
}

float PeripheralLayer::Configuration::UnavailableGear()
{
	return std::numeric_limits<float>::quiet_NaN();
}

uint16_t PeripheralLayer::Configuration::GetVSSPulsesPerKm() const
{
	return m_VSSPulsesPerKm;
}

uint16_t PeripheralLayer::Configuration::GetInjectorFlow() const
{
	return m_InjectorFlow;
}

uint8_t PeripheralLayer::Configuration::GetInjectorCount() const
{
	return m_InjectorCount;
}

uint8_t PeripheralLayer::Configuration::GetInjectorMechanicalDelay() const
{
	return m_InjectorMechanicalDelay;
}

uint16_t PeripheralLayer::Configuration::GetFuelPressure() const
{
	return m_FuelPressure;
}

uint32_t PeripheralLayer::Configuration::GetMicrosecondsPerLiter() const
{
	const uint16_t injectorFlowAtPressure = 3000;

	float injectorFlowLiterPerMinute = GetInjectorFlow() / 1000.f;
	float microsecondsPerLiter = (60.f * 1000000.f) / injectorFlowLiterPerMinute;

	return static_cast<uint32_t>(std::sqrt(GetFuelPressure() / injectorFlowAtPressure) * microsecondsPerLiter);
}
