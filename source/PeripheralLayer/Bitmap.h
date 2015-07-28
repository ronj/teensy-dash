#pragma once

#include <cinttypes>

namespace PeripheralLayer
{
	namespace Bitmaps
	{
		struct Bitmap
		{
			uint8_t width;
			uint8_t height;
			const uint8_t* data;
		};
	}
}
