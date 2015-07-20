#pragma once

#include "FrequencyCounter.h"

namespace HardwareLayer
{
	class TeensyFrequencyCounter
		: public FrequencyCounter
	{
	public:
		TeensyFrequencyCounter();
		virtual ~TeensyFrequencyCounter();

		virtual bool Available();
		virtual uint32_t Read();
		virtual float CountToFrequency(uint32_t count);
	};
}
