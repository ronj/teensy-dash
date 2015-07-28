#pragma once

#include "Platform.h"

#include "Snooze.h"

namespace HardwareLayer
{
	class TeensyPlatform : public Platform
	{
	public:
		TeensyPlatform();
		virtual ~TeensyPlatform();

		virtual void Init();
		virtual void KickWatchdog();
		virtual void LowPowerSleep(uint32_t milliseconds);
		virtual void Idle();

	private:
		void LogResetReason() const;

	private:
		SnoozeBlock m_LowPowerConfiguration;
	};
}
