#pragma once

#include <cinttypes>

namespace PeripheralLayer
{
	class PulseCounter
	{
	public:
		PulseCounter();

		uint32_t GetCount();
	};
}
