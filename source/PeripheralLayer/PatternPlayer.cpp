#include "PatternPlayer.h"

#include "PeripheralLayer/Color.h"
#include "PeripheralLayer/LedPatterns.h"
#include "HardwareLayer/LedDriver.h"

PeripheralLayer::PatternPlayer::PatternPlayer(HardwareLayer::LedDriver& driver)
	: m_Driver(driver)
{
}

void PeripheralLayer::PatternPlayer::Set(LedPattern& pattern)
{
    m_CurrentPattern = &pattern;
}

uint8_t PeripheralLayer::PatternPlayer::Width() const
{
    return m_Driver.Width();
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
    m_CurrentPattern->Update(*this, tickcount);
	m_Driver.Update();
}
