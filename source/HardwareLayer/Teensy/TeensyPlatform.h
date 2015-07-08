#pragma once

#include "Platform.h"

namespace HardwareLayer
{
	class TeensyPlatform : public Platform
	{
	public:
		TeensyPlatform();
		virtual ~TeensyPlatform();

		virtual void Init();
		virtual void KickWatchdog();

	private:
		void LogResetReason() const;
	};
}
