#pragma once

#include <cinttypes>

namespace PeripheralLayer
{
	namespace Fonts
	{
		struct Descriptor
		{
			uint8_t width;
			uint8_t height;
			uint16_t offset;
		};

		struct Font
		{
			const Descriptor* descriptor;
			const uint8_t* data;
			int16_t kerning;
			uint8_t StartCharacter() const { return data[0]; }
			uint8_t EndCharacter() const { return data[1]; }
		};
	}
}
