#pragma once

#include <cinttypes>

#include "Common/NonCopyable.h"

namespace HardwareLayer
{
	class AnalogPin
		: public Common::NonCopyable
	{
	public:
		virtual uint16_t Read() const = 0;
		virtual void Write(uint16_t) = 0;
	};
}
