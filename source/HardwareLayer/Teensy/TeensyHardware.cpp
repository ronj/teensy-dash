#include "TeensyHardware.h"

HardwareLayer::TeensyHardware::TeensyHardware()
	: m_XPin(A0)
	, m_YPin(A1)
	, m_ZPin(A2)
	, m_BacklightPin(6)
	, m_VSSPin(23)
	, m_RPMPin(22)
	, m_AccelerometerDriver(m_XPin, m_YPin, m_ZPin, m_Timer)
{
	m_Platform.Init();
	m_BacklightPin.Write(150);
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

HardwareLayer::RotaryEncoder& HardwareLayer::TeensyHardware::GetRotaryEncoder()
{
	return m_RotaryEncoder;
}

HardwareLayer::DigitalPin& HardwareLayer::TeensyHardware::GetVSSPin()
{
    return m_VSSPin;
}

HardwareLayer::DigitalPin& HardwareLayer::TeensyHardware::GetRPMPin()
{
    return m_RPMPin;
}
