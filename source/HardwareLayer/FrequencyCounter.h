#pragma once

#include "Common/NonCopyable.h"

#include <cinttypes>

namespace HardwareLayer
{
	class FrequencyCounter
		: public Common::NonCopyable
	{
	public:
		virtual bool Available() = 0;
		virtual uint32_t Read() = 0;
		virtual float CountToFrequency(uint32_t count) = 0;
	};
}
