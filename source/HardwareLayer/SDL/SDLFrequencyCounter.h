#pragma once

#include "FrequencyCounter.h"

namespace HardwareLayer
{
	class SDLFrequencyCounter
		: public FrequencyCounter
	{
	public:
		virtual bool Available();
		virtual uint32_t Read();
		virtual float CountToFrequency(uint32_t);
	};
}
