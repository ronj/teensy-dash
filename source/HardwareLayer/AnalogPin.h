#pragma once

#include <cinttypes>

namespace HardwareLayer
{
	class AnalogPin
	{
	public:
		virtual uint16_t Read() const = 0;
		virtual void Write(uint16_t) = 0;
	};
}
