#include "NeoPixelLedDriver.h"

HardwareLayer::NeoPixelLedDriver::NeoPixelLedDriver(uint8_t pin)
	: m_Driver(Width(), pin, NEO_GRB + NEO_KHZ800)
{
	m_Driver.begin();
	Update();
}

void HardwareLayer::NeoPixelLedDriver::DrawPixel(int16_t x, int16_t y, uint32_t color)
{
	m_Driver.setPixelColor(x, color);
}

bool HardwareLayer::NeoPixelLedDriver::DrawVerticalLine(int16_t, int16_t, int16_t, uint32_t)
{
	return false;
}

bool HardwareLayer::NeoPixelLedDriver::DrawHorizontalLine(int16_t, int16_t, int16_t, uint32_t)
{
	return false;
}

bool HardwareLayer::NeoPixelLedDriver::FillRect(int16_t, int16_t, int16_t, int16_t, uint32_t)
{
	return false;
}

void HardwareLayer::NeoPixelLedDriver::Update()
{
	m_Driver.show();
}
