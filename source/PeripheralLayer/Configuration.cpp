#include "Configuration.h"

#include <limits>

PeripheralLayer::Configuration::Configuration()
	: m_AccelerometerXCalibration(403, 604)
	, m_AccelerometerYCalibration(401, 599)
	, m_AccelerometerZCalibration(398, 608)
	, m_TireWidth(205)
	, m_TireAspect(40)
	, m_RimSize(17)
	//, m_FinalDrive(4.05f)
	//, m_GearRatios({ { 2.92f, 1.87f, 1.41f, 1.15f, 0.92f, 0.79f } })
	, m_FinalDrive(4.06f)
	, m_GearRatios({ { 3.42f, 1.81f, 1.28f, 0.98f, 0.77f, std::numeric_limits<float>::quiet_NaN() } })
	, m_VSSPulsesPerKm(4500)
	, m_PulsesPerRPM(1)
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

uint16_t PeripheralLayer::Configuration::GetVSSPulsesPerKm() const
{
	return m_VSSPulsesPerKm;
}

uint8_t PeripheralLayer::Configuration::GetPulsesPerRPM() const
{
	return m_PulsesPerRPM;
}
