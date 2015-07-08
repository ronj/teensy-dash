#pragma once

namespace HardwareLayer
{
	class Platform
	{
	public:
		virtual void Init() = 0;
		virtual void KickWatchdog() = 0;
	};
}
