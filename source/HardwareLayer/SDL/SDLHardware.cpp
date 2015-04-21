#include "SDLHardware.h"

HardwareLayer::SDLHardware::SDLHardware()
	: m_AccelerometerDriver(m_X, m_Y, m_Z, m_Timer)
{
	m_Platform.Init();
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
