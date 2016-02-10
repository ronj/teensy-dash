#pragma once

#include <cstdint>

namespace HardwareLayer
{
	class LedDriver;
}

namespace PeripheralLayer
{
	class PatternPlayer
	{
	public:
		PatternPlayer(HardwareLayer::LedDriver& driver);

		void DrawPixel(int16_t x, uint32_t color);
		void Clear();

		void Update();

	private:
		HardwareLayer::LedDriver& m_Driver;
	};
}
