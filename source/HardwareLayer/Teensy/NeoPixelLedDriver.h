#pragma once

#include "DisplayDriver.h"

#include <Adafruit_NeoPixel.h>

namespace HardwareLayer
{
	class NeoPixelLedDriver : public DisplayDriver
	{
	public:
		NeoPixelLedDriver(uint8_t pin);

		virtual uint16_t Width() const { return 8; }
		virtual uint16_t Height() const { return 1; }

		virtual void DrawPixel(int16_t x, int16_t y, uint32_t color);
		virtual bool DrawVerticalLine(int16_t, int16_t, int16_t, uint32_t);
		virtual bool DrawHorizontalLine(int16_t, int16_t, int16_t, uint32_t);
		virtual bool FillRect(int16_t, int16_t, int16_t, int16_t, uint32_t);

		virtual void Update();

	private:
		Adafruit_NeoPixel m_Driver;
	};
}
