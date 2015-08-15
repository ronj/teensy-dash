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

HardwareLayer::DisplayDriver& HardwareLayer::SDLHardware::GetLedDriver()
{
	return m_LedDriver;
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

HardwareLayer::DigitalPin& HardwareLayer::SDLHardware::GetParkingSensorPin()
{
	return m_ParkingSensorPin;
}

HardwareLayer::FrequencyCounter& HardwareLayer::SDLHardware::GetRPMFrequencyCounter()
{
	return m_RPMFrequencyCounter;
}

const HardwareLayer::AnalogPin& HardwareLayer::SDLHardware::GetBatteryVoltagePin()
{
	return m_BatteryVoltagePin;
}

HardwareLayer::AnalogPin& HardwareLayer::SDLHardware::GetBacklightPin()
{
    return m_BacklightPin;
}
