#pragma once

#include <cinttypes>

namespace HardwareLayer
{
	class Timer;
}

namespace PeripheralLayer
{
	class TimeProvider
	{
	public:
		TimeProvider(HardwareLayer::Timer& driver);

		uint32_t TickCountMilliseconds();
		uint32_t TickCountMicroseconds();

		void Sleep(uint32_t milliseconds);

	private:
		HardwareLayer::Timer& m_Timer;
	};
}
