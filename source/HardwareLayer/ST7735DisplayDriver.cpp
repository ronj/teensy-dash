#include "ST7735DisplayDriver.h"

HardwareLayer::ST7735DisplayDriver::ST7735DisplayDriver()
	: m_Driver(10, 9, 8)
{
	m_Driver.initR(INITR_REDTAB);
	m_Driver.setBitrate(24000000);
}

void HardwareLayer::ST7735DisplayDriver::DrawPixel(int16_t x, int16_t y, uint32_t color)
{
	m_Driver.drawPixel(x, y, m_Driver.Color565(color >> 24, color >> 16, color >> 8));
}

bool HardwareLayer::ST7735DisplayDriver::DrawVerticalLine(int16_t, int16_t, int16_t, uint32_t)
{
	return false;
}

bool HardwareLayer::ST7735DisplayDriver::DrawHorizontalLine(int16_t, int16_t, int16_t, uint32_t)
{
	return false;
}

bool HardwareLayer::ST7735DisplayDriver::FillRect(int16_t, int16_t, int16_t, int16_t, uint32_t)
{
	return false;
}
