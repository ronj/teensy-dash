#include "LedPatterns.h"

#include "PeripheralLayer/Color.h"
#include "PeripheralLayer/PatternPlayer.h"

void PeripheralLayer::OffPattern::Update(PeripheralLayer::PatternPlayer& player, uint32_t)
{
    player.Clear();
}

PeripheralLayer::BlinkPattern::BlinkPattern(uint32_t blinkperiod)
    : m_BlinkPeriod(blinkperiod)
{
}

void PeripheralLayer::BlinkPattern::Update(PeripheralLayer::PatternPlayer& player, uint32_t tickcount)
{
    if (tickcount - m_PreviousBlink > m_BlinkPeriod)
    {
        for (int i = 0; i < player.Width(); i++)
        {
            player.DrawPixel(i, m_BlinkState ? PeripheralLayer::Color::RGB(50, 0, 0).ToRGB() : 0);
        }

        m_BlinkState = !m_BlinkState;
        m_PreviousBlink = tickcount;
    }
}

void PeripheralLayer::BarFillPattern::Update(PeripheralLayer::PatternPlayer& player, uint32_t)
{
    for (uint8_t i = 0; i < m_BarLength; ++i)
    {
        uint32_t color = i < 3 ? PeripheralLayer::Color::RGB(0, 20, 0).ToRGB() : PeripheralLayer::Color::RGB(20, 0, 0).ToRGB();
        player.DrawPixel(i, i < m_BarLength ? color : 0);
    }
}

void PeripheralLayer::BarFillPattern::SetBarLength(uint8_t length)
{
    m_BarLength = length;
}

void PeripheralLayer::ScanPattern::Update(PeripheralLayer::PatternPlayer& player, uint32_t tickcount)
{
    player.Clear();
    player.DrawPixel(m_Position, PeripheralLayer::Color::RGB(5, 20, 0).ToRGB());

    if (tickcount > m_PreviousIncrement + m_IncrementPeriod)
    {
    	m_Position = (m_Position + 1) % player.Width();
    	m_IncrementPeriod = tickcount;
    }
}
