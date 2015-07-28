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
			const uint8_t startCharacter;
			const uint8_t endCharacter;
			int8_t kerning;
			const Descriptor* descriptor;
			const uint8_t* data;
			uint8_t StartCharacter() const { return startCharacter; }
			uint8_t EndCharacter() const { return endCharacter; }
		};
	}
}
