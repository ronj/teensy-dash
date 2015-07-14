#pragma once

#include "DisplayDriver.h"

namespace HardwareLayer
{
	class SDLLedDriver : public DisplayDriver
	{
	public:
		virtual uint16_t Width() const { return 8; }
		virtual uint16_t Height() const { return 1; }

		virtual void DrawPixel(int16_t x, int16_t y, uint32_t color) {}
		virtual bool DrawVerticalLine(int16_t, int16_t, int16_t, uint32_t) { return false; }
		virtual bool DrawHorizontalLine(int16_t, int16_t, int16_t, uint32_t) { return false; }
		virtual bool FillRect(int16_t, int16_t, int16_t, int16_t, uint32_t) { return false; }

		virtual void Update() {}
	};
}
