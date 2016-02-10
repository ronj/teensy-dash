#include "NeoPixelLedDriver.h"

HardwareLayer::NeoPixelLedDriver::NeoPixelLedDriver(uint8_t pin)
	: m_Driver(8, pin, NEO_GRB + NEO_KHZ800)
{
	m_Driver.begin();
	Update();
}

void HardwareLayer::NeoPixelLedDriver::SetPixel(int16_t x, uint32_t color)
{
	m_Driver.setPixelColor(x, color);
}

void HardwareLayer::NeoPixelLedDriver::Clear()
{
	m_Driver.clear();
}

void HardwareLayer::NeoPixelLedDriver::Update()
{
	m_Driver.show();
}
