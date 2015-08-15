#pragma once

#include <cinttypes>

namespace HardwareLayer
{
	class Timer
	{
	public:
		virtual uint32_t TickCountMilliseconds() const = 0;
		virtual uint32_t TickCountMicroseconds() const = 0;
		virtual void Sleep(uint32_t milliseconds) const = 0;
	};
}
