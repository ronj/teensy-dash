#pragma once

#include <cstdint>

namespace HardwareLayer
{
	class LedDriver;
}

namespace PeripheralLayer
{
    class LedPattern;

	class PatternPlayer
	{
	public:
		PatternPlayer(HardwareLayer::LedDriver& driver);

        void Set(LedPattern& pattern);

        uint8_t Width() const;
		void DrawPixel(int16_t x, uint32_t color);
		void Clear();

		void Update(uint32_t tickcount);

	private:
		HardwareLayer::LedDriver& m_Driver;
        LedPattern* m_CurrentPattern = nullptr;
	};
}
