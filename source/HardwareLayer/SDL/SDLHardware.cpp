#include "SDLHardware.h"

HardwareLayer::SDLHardware::SDLHardware()
	: m_AccelerometerDriver(m_X, m_Y, m_Z, m_Timer)
	, m_BatteryVoltagePin()
{
	m_Platform.Init();
}

HardwareLayer::Platform& HardwareLayer::SDLHardware::GetPlatform()
{
	return m_Platform;
}

HardwareLayer::AccelerometerDriver& HardwareLayer::SDLHardware::GetAccelerometerDriver()
{
	return m_AccelerometerDriver;
}

HardwareLayer::DisplayDriver& HardwareLayer::SDLHardware::GetDisplayDriver()
{
	return m_DisplayDriver;
}

HardwareLayer::Timer& HardwareLayer::SDLHardware::GetTimer()
{
	return m_Timer;
}

HardwareLayer::RotaryEncoder& HardwareLayer::SDLHardware::GetRotaryEncoder()
{
	return m_RotaryEncoder;
}

HardwareLayer::DigitalPin& HardwareLayer::SDLHardware::GetVSSPin()
{
    return m_VSSPin;
}

HardwareLayer::DigitalPin& HardwareLayer::SDLHardware::GetRPMPin()
{
    return m_RPMPin;
}

const HardwareLayer::AnalogPin& HardwareLayer::SDLHardware::GetBatteryVoltagePin()
{
	return m_BatteryVoltagePin;
}
