#pragma once

#include <cinttypes>

namespace HardwareLayer
{
	class Platform
	{
	public:
		virtual void Init() = 0;
		virtual void KickWatchdog() = 0;
		virtual void LowPowerSleep(uint32_t microseconds) = 0;
		virtual void Idle() = 0;
	};
}
