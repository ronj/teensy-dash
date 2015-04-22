#define CPU_RESTART_ADDR (uint32_t *)0xE000ED0C
#define CPU_RESTART_VAL 0x5FA0004
#define CPU_RESTART (*CPU_RESTART_ADDR = CPU_RESTART_VAL);

#include "TeensyPlatform.h"

#include "Common/ArduinoWrapper.h"

HardwareLayer::TeensyPlatform::TeensyPlatform()
{
	Serial.begin(57600);
}

HardwareLayer::TeensyPlatform::~TeensyPlatform()
{
	CPU_RESTART;
}

void HardwareLayer::TeensyPlatform::Init()
{
}
