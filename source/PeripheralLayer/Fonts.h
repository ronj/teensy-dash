#pragma once

#include "Font.h"

#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#else
#define PROGMEM
#endif

namespace PeripheralLayer
{
	namespace Fonts
	{
		extern const uint8_t TimesNewRoman_8PT_Data[];
		extern const Descriptor TimesNewRoman_8PT_Descriptor[];

		static const Font TimesNewRoman = { TimesNewRoman_8PT_Descriptor, TimesNewRoman_8PT_Data, 1 };

		extern const uint8_t GLCDFont_Data[];
		extern const Descriptor GLCDFont_Descriptor[];

		static const Font LCDFont = { GLCDFont_Descriptor, GLCDFont_Data, 1 };
	}
}
