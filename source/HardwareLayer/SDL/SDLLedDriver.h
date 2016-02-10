#pragma once

#include "LedDriver.h"

namespace HardwareLayer
{
	class SDLLedDriver : public LedDriver
	{
	public:
		virtual uint16_t Width() const { return 8; }

		virtual void SetPixel(int16_t x, uint32_t color) {}
		virtual void Clear() {}

		virtual void Update() {}
	};
}
