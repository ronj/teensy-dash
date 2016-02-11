#pragma once

#include <cstdint>

namespace HardwareLayer
{
	class LedDriver;
}

namespace PeripheralLayer
{
    class LedPattern
    {
    public:
        virtual void operator()(HardwareLayer::LedDriver& leds, uint32_t tickcount) = 0;
    };

    class OffPattern : public LedPattern
    {
    public:
        void operator()(HardwareLayer::LedDriver& leds, uint32_t);
    };

    class BlinkPattern : public LedPattern
    {
    public:
        BlinkPattern(uint32_t blinkdelay);
        void operator()(HardwareLayer::LedDriver& leds, uint32_t tickcount);

    private:
        bool m_BlinkState = false;
        uint32_t m_PreviousBlink = 0;
        uint32_t m_BlinkPeriod = 0;
    };

	class PatternPlayer
	{
	public:
		PatternPlayer(HardwareLayer::LedDriver& driver);

        void Set(LedPattern& pattern);

		void DrawPixel(int16_t x, uint32_t color);
		void Clear();

		void Update(uint32_t tickcount);

	private:
		HardwareLayer::LedDriver& m_Driver;
        LedPattern* m_CurrentPattern = nullptr;
	};
}
