#include "TeensyHardware.h"

HardwareLayer::TeensyHardware::TeensyHardware()
	: m_XPin(A0)
	, m_YPin(A1)
	, m_ZPin(A2)
	, m_BacklightPin(6)
	, m_BatteryVoltagePin(22)
	, m_VSSPin(23, PinType::Input)
	, m_InjectorPin(21, PinType::Input)
	, m_ParkingSensorPin(5, PinType::Input)
	, m_ButtonPin(7, PinType::InputPullUp)
	, m_AccelerometerDriver(m_XPin, m_YPin, m_ZPin)
	, m_LedDriver(2)
	, m_RotaryEncoder()
{
	m_Platform.Init();
	m_BacklightPin.Write(0);
}

HardwareLayer::Platform& HardwareLayer::TeensyHardware::GetPlatform()
{
	return m_Platform;
}

HardwareLayer::AccelerometerDriver& HardwareLayer::TeensyHardware::GetAccelerometerDriver()
{
	return m_AccelerometerDriver;
}

HardwareLayer::DisplayDriver& HardwareLayer::TeensyHardware::GetDisplayDriver()
{
	return m_DisplayDriver;
}

HardwareLayer::DisplayDriver& HardwareLayer::TeensyHardware::GetLedDriver()
{
	return m_LedDriver;
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

HardwareLayer::DigitalPin& HardwareLayer::TeensyHardware::GetInjectorPin()
{
    return m_InjectorPin;
}

HardwareLayer::DigitalPin& HardwareLayer::TeensyHardware::GetParkingSensorPin()
{
	return m_ParkingSensorPin;
}

HardwareLayer::DigitalPin& HardwareLayer::TeensyHardware::GetButtonPin()
{
	return m_ButtonPin;
}

HardwareLayer::FrequencyCounter& HardwareLayer::TeensyHardware::GetRPMFrequencyCounter()
{
	return m_RPMFrequencyCounter;
}

const HardwareLayer::AnalogPin& HardwareLayer::TeensyHardware::GetBatteryVoltagePin()
{
    return m_BatteryVoltagePin;
}

HardwareLayer::AnalogPin& HardwareLayer::TeensyHardware::GetBacklightPin()
{
    return m_BacklightPin;
}
