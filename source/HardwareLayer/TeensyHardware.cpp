#include "TeensyHardware.h"

HardwareLayer::TeensyHardware::TeensyHardware()
	: m_XPin(A2)
	, m_YPin(A3)
	, m_ZPin(A4)
	, m_AccelerometerDriver(m_XPin, m_YPin, m_ZPin, m_Timer)
{
}

HardwareLayer::AccelerometerDriver& HardwareLayer::TeensyHardware::GetAccelerometerDriver()
{
	return m_AccelerometerDriver;
}

HardwareLayer::DisplayDriver& HardwareLayer::TeensyHardware::GetDisplayDriver()
{
	return m_DisplayDriver;
}

HardwareLayer::Timer& HardwareLayer::TeensyHardware::GetTimer()
{
	return m_Timer;
}
