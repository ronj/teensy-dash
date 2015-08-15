#include "PowerManagement.h"

#include "Common/Logger.h"

#include "HardwareLayer/AnalogPin.h"
#include "HardwareLayer/DigitalPin.h"
#include "HardwareLayer/Hardware.h"
#include "HardwareLayer/Platform.h"

PeripheralLayer::PowerManagement::PowerManagement(HardwareLayer::Hardware& hardware)
  : m_Hardware(hardware)
{
}

void PeripheralLayer::PowerManagement::PowerDownPeripherals()
{
	LOG_METHOD_ENTRY;

	m_Hardware.GetBacklightPin().Write(0);
	m_Hardware.GetVSSPin().DisableInterrupt();
}

void PeripheralLayer::PowerManagement::PowerUpPeripherals()
{
	LOG_METHOD_ENTRY;

	m_Hardware.GetVSSPin().EnableInterrupt(HardwareLayer::InterruptType::Rising);
	m_Hardware.GetBacklightPin().Write(100);
}

void PeripheralLayer::PowerManagement::LowPowerSleep()
{
	LOG_METHOD_ENTRY;

	m_Hardware.GetPlatform().LowPowerSleep(1000 * 2);
}
