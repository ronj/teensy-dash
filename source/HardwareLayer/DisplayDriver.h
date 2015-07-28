#pragma once

#include <cinttypes>

namespace HardwareLayer
{
	class DisplayDriver
	{
	public:
		virtual uint16_t Width() const = 0;
		virtual uint16_t Height() const = 0;

		virtual void DrawPixel(int16_t x, int16_t y, uint32_t color) = 0;
		virtual bool DrawVerticalLine(int16_t x, int16_t y, int16_t h, uint32_t color) = 0;
		virtual bool DrawHorizontalLine(int16_t x, int16_t y, int16_t w, uint32_t color) = 0;
		virtual bool FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color) = 0;

		virtual void Update() = 0;
	};
}
