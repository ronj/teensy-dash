#include "PatternPlayer.h"

#include "PeripheralLayer/Color.h"

#include "HardwareLayer/LedDriver.h"

void PeripheralLayer::OffPattern::operator()(HardwareLayer::LedDriver& leds, uint32_t)
{
    leds.Clear();
}

PeripheralLayer::BlinkPattern::BlinkPattern(uint32_t blinkperiod)
    : m_BlinkPeriod(blinkperiod)
{
}

void PeripheralLayer::BlinkPattern::operator()(HardwareLayer::LedDriver& leds, uint32_t tickcount)
{
    if (tickcount - m_PreviousBlink > m_BlinkPeriod)
    {
        for (int i = 0; i < leds.Width(); i++)
        {
            leds.SetPixel(i, m_BlinkState ? PeripheralLayer::Color::RGB(50, 0, 0).ToRGB() : 0);
        }

        m_BlinkState = !m_BlinkState;
        m_PreviousBlink = tickcount;
    }
}

PeripheralLayer::PatternPlayer::PatternPlayer(HardwareLayer::LedDriver& driver)
	: m_Driver(driver)
{
}

void PeripheralLayer::PatternPlayer::Set(LedPattern& pattern)
{
    m_CurrentPattern = &pattern;
}

void PeripheralLayer::PatternPlayer::DrawPixel(int16_t x, uint32_t color)
{
	m_Driver.SetPixel(x, color);
}

void PeripheralLayer::PatternPlayer::Clear()
{
	m_Driver.Clear();
}

void PeripheralLayer::PatternPlayer::Update(uint32_t tickcount)
{
    (*m_CurrentPattern)(m_Driver, tickcount);
	m_Driver.Update();
}
