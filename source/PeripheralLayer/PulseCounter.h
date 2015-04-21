#pragma once

#include <cinttypes>

namespace PeripheralLayer
{
	class PulseCounter
	{
	public:
		PulseCounter();

		virtual uint32_t GetCount();
	};
}
