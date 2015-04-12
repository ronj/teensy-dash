#pragma once

#include "AnalogPin.h"

namespace HardwareLayer
{
	class SDLAnalogPin
		: public AnalogPin
	{
	public:
		virtual uint16_t Read() const;
		virtual void Write(uint16_t value);
	};
}
