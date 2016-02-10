#pragma once

#include <cinttypes>

namespace HardwareLayer
{
	class LedDriver
	{
	public:
		virtual uint16_t Width() const = 0;

		virtual void SetPixel(int16_t x, uint32_t color) = 0;
		virtual void Clear() = 0;

		virtual void Update() = 0;
	};
}
