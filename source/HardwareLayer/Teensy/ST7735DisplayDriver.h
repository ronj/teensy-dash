#pragma once

#include "DisplayDriver.h"

#include <Adafruit_ST7735.h>

#undef swap
#undef min
#undef max

namespace HardwareLayer
{
	class ST7735DisplayDriver : public DisplayDriver
	{
	public:
		ST7735DisplayDriver();

		virtual uint16_t Width() const { return 128; }
		virtual uint16_t Height() const { return 160; }

		virtual void DrawPixel(int16_t x, int16_t y, uint32_t color);
		virtual bool DrawVerticalLine(int16_t, int16_t, int16_t, uint32_t);
		virtual bool DrawHorizontalLine(int16_t, int16_t, int16_t, uint32_t);
		virtual bool FillRect(int16_t, int16_t, int16_t, int16_t, uint32_t);

		virtual void Update() {};

	private:
		Adafruit_ST7735 m_Driver;
	};
}
