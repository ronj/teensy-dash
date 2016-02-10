#pragma once

#include "LedDriver.h"

#include <Adafruit_NeoPixel.h>

namespace HardwareLayer
{
	class NeoPixelLedDriver : public LedDriver
	{
	public:
		NeoPixelLedDriver(uint8_t pin);

		virtual uint16_t Width() const { return m_Driver.numPixels(); }

		virtual void SetPixel(int16_t x, uint32_t color);
		virtual void Clear();

		virtual void Update();

	private:
		Adafruit_NeoPixel m_Driver;
	};
}
