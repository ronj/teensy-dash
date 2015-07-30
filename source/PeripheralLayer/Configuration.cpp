#include "Configuration.h"

#include <limits>

PeripheralLayer::Configuration::Configuration()
	: m_AccelerometerXCalibration(403, 604)
	, m_AccelerometerYCalibration(401, 599)
	, m_AccelerometerZCalibration(398, 608)
	, m_TireWidth(205)
	, m_TireAspect(40)
	, m_RimSize(17)
	, m_FinalDrive(60.f / 14.f)
	, m_GearRatios({ { 41.f / 12.f, 38.f / 21.f, 37.f / 29.f, 39.f / 40.f, 33.f / 43.f, UnavailableGear() } })
	, m_VSSPulsesPerKm(4971)
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
