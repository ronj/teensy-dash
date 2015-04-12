#pragma once

#include "Timer.h"

namespace HardwareLayer
{
	class TeensyTimer : public Timer
	{
	public:
		virtual uint32_t TickCountMilliseconds() const;
		virtual uint32_t TickCountMicroseconds() const;

		virtual void Sleep(uint32_t milliseconds) const;
	};
}
