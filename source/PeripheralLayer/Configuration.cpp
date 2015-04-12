#include "Configuration.h"

PeripheralLayer::Configuration::Configuration()
	: m_AccelerometerXCalibration(403, 604)
	, m_AccelerometerYCalibration(401, 599)
	, m_AccelerometerZCalibration(398, 408)
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
