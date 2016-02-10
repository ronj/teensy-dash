#include "PatternPlayer.h"

#include "HardwareLayer/LedDriver.h"

PeripheralLayer::PatternPlayer::PatternPlayer(HardwareLayer::LedDriver& driver)
	: m_Driver(driver)
{
}

void PeripheralLayer::PatternPlayer::DrawPixel(int16_t x, uint32_t color)
{
	m_Driver.SetPixel(x, color);
}

void PeripheralLayer::PatternPlayer::Clear()
{
	m_Driver.Clear();
}

void PeripheralLayer::PatternPlayer::Update()
{
	m_Driver.Update();
}
