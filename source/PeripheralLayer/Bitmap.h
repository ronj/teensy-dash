#pragma once

#include <cinttypes>

namespace PeripheralLayer
{
	namespace Bitmaps
	{
		struct Bitmap
		{
			const uint8_t width;
			const uint8_t height;
			const uint8_t* data;
		};
	}
}
