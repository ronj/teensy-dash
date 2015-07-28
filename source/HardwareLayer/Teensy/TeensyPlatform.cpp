#include "TeensyPlatform.h"

#include "Common/ArduinoWrapper.h"
#include "Common/DisableInterruptContext.h"
#include "Common/Logger.h"

#define CPU_RESTART_ADDR (uint32_t *)0xE000ED0C
#define CPU_RESTART_VAL 0x5FA0004
#define CPU_RESTART (*CPU_RESTART_ADDR = CPU_RESTART_VAL);

#ifdef __cplusplus
extern "C" {
#endif
int _kill(int, int)
{
	return 0;
}

int _getpid()
{
	return 0;
}
#ifdef __cplusplus
}
#endif

HardwareLayer::TeensyPlatform::TeensyPlatform()
{
}

HardwareLayer::TeensyPlatform::~TeensyPlatform()
{
	CPU_RESTART;
}

void HardwareLayer::TeensyPlatform::Init()
{
	LogResetReason();
}

void HardwareLayer::TeensyPlatform::KickWatchdog()
{
	Common::DisableInterruptContext disable;
	WDOG_REFRESH = 0xA602;
	WDOG_REFRESH = 0xB480;
}

void HardwareLayer::TeensyPlatform::LowPowerSleep(uint32_t milliseconds)
{
	m_LowPowerConfiguration.setTimer(milliseconds);
	Snooze.hibernate(m_LowPowerConfiguration);
}

void HardwareLayer::TeensyPlatform::Idle()
{
	Snooze.idle();
}

void HardwareLayer::TeensyPlatform::LogResetReason() const
{
	uint16_t mask = 1;
	uint16_t reason = RCM_SRS0 | RCM_SRS1 << 8;

	Common::Logger& logger = Common::Logger::Get();

	logger.Log("Reset reason: ");

	do
	{
		switch (reason & mask)
		{
			case 0x0001: logger.LogLine("Wakeup"); break;
			case 0x0002: logger.LogLine("Low-voltage Detect"); break;
			case 0x0004: logger.LogLine("Loss of Clock"); break;
			case 0x0008: logger.LogLine("Loss of Lock"); break;
			//case 0x0010: Reserved
			case 0x0020: logger.LogLine("Watchdog"); break;
			case 0x0040: logger.LogLine("External Pin"); break;
			case 0x0080: logger.LogLine("Power-on"); break;

			case 0x0100: logger.LogLine("JTAG"); break;
			case 0x0200: logger.LogLine("Core Lockup Event"); break;
			case 0x0400: logger.LogLine("Software"); break;
			case 0x0800: logger.LogLine("MDM-AP"); break;

			case 0x1000: logger.LogLine("EzPort"); break;
			case 0x2000: logger.LogLine("Stop Mode Acknowledge Error"); break;
			case 0x8000: logger.LogLine("Tamper Detect"); break;
		}

	} while (mask <<= 1);
}
