#pragma once

#include <cinttypes>

namespace PeripheralLayer
{
	struct FontDescriptor
	{
		uint8_t width;
		uint8_t height;
		uint16_t offset;
	};

	extern const uint8_t arial_8ptBitmaps[];
	extern const FontDescriptor arial_8ptDescriptors[];
}
