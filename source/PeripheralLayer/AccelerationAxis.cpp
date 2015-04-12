#include "AccelerationAxis.h"

#include "Common/Math.h"

#include "PeripheralLayer/Configuration.h"

#include "HardwareLayer/AccelerometerDriver.h"

PeripheralLayer::AccelerationAxis::AccelerationAxis(HardwareLayer::AccelerometerDriver& driver, PeripheralLayer::Configuration& configuration, Axis axis)
	: m_Driver(driver)
	, m_Configuration(configuration)
	, m_Axis(axis)
{
}

int32_t PeripheralLayer::AccelerationAxis::GetValue() const
{
	switch (m_Axis)
	{
		case Axis::X : return Common::Math::Map(m_Driver.GetXAcceleration(), m_Configuration.GetAccelerometerXCalibration().Min, m_Configuration.GetAccelerometerXCalibration().Max, -1000, 1000);
		case Axis::Y : return Common::Math::Map(m_Driver.GetYAcceleration(), m_Configuration.GetAccelerometerYCalibration().Min, m_Configuration.GetAccelerometerYCalibration().Max, -1000, 1000);
		case Axis::Z : return Common::Math::Map(m_Driver.GetZAcceleration(), m_Configuration.GetAccelerometerZCalibration().Min, m_Configuration.GetAccelerometerZCalibration().Max, -1000, 1000);
	}

	return 0;
}
