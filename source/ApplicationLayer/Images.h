#pragma once

#ifdef __AVR__
	#include <avr/io.h>
	#include <avr/pgmspace.h>
#else
	#define PROGMEM
#endif

namespace ApplicationLayer
{
    namespace Images
    {
		static const unsigned char Battery[] PROGMEM =
        {
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x07, 0xC0, 0x03, 0xE0, 0x07, 0xC0, 0x03, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
			0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0xC3, 0xC0, 0x00, 0x00, 0xC3, 0xC7, 0xC0, 0x03, 0xF3,
			0xC7, 0xC0, 0x03, 0xF3, 0xC0, 0x00, 0x00, 0xC3, 0xC0, 0x00, 0x00, 0xC3, 0xC0, 0x00, 0x00, 0x03,
			0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x03,
			0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x03,
			0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF,
			0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };

        static const unsigned char Fuelpump[] PROGMEM =
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xE0, 0x00, 0x07, 0xFF, 0xE0, 0x00,
            0x04, 0x00, 0x20, 0x00, 0x04, 0x00, 0x20, 0x00, 0x04, 0x00, 0x22, 0x00, 0x04, 0x00, 0x23, 0x00,
            0x04, 0x00, 0x21, 0x80, 0x04, 0x00, 0x20, 0xC0, 0x04, 0x00, 0x20, 0xE0, 0x04, 0x00, 0x20, 0x40,
            0x07, 0xFF, 0xE0, 0x40, 0x07, 0xFF, 0xF8, 0x60, 0x07, 0xFF, 0xE4, 0x20, 0x07, 0xFF, 0xE4, 0x30,
            0x07, 0xFF, 0xE4, 0x10, 0x07, 0xFF, 0xE4, 0x10, 0x07, 0xFF, 0xE8, 0x10, 0x07, 0xFF, 0xE8, 0x10,
            0x07, 0xFF, 0xE8, 0x10, 0x07, 0xFF, 0xE8, 0x10, 0x07, 0xFF, 0xE8, 0x10, 0x07, 0xFF, 0xE8, 0x10,
            0x07, 0xFF, 0xE8, 0x10, 0x07, 0xFF, 0xE6, 0x60, 0x07, 0xFF, 0xE1, 0x80, 0x07, 0xFF, 0xE0, 0x00,
            0x0F, 0xFF, 0xF0, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };

        static const unsigned char Oilcan[] PROGMEM =
		{
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x38, 0xFC, 0x00, 0x00, 0x70, 0x30, 0x00, 0x00,
            0xFF, 0xFF, 0xE0, 0x18, 0xDF, 0xFF, 0xF0, 0x3C, 0x18, 0x00, 0x38, 0x76, 0x18, 0x00, 0x1F, 0xE2,
            0x18, 0x00, 0x0E, 0x60, 0x18, 0x00, 0x04, 0xE2, 0x18, 0x00, 0x01, 0xC5, 0x18, 0x00, 0x03, 0x85,
            0x18, 0x00, 0x07, 0x02, 0x1F, 0xFF, 0xFE, 0x00, 0x1F, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };

		static const unsigned char Temperature[] PROGMEM =
		{
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0xF8, 0x00,
			0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00,
			0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0x80, 0x00,
			0x00, 0x01, 0x80, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x07, 0xE0, 0x00, 0x30, 0x07, 0xE0, 0x0C,
			0x1C, 0x07, 0xE0, 0x38, 0x07, 0x33, 0xCC, 0xE0, 0x01, 0xE0, 0x07, 0x80, 0x60, 0xC3, 0xC3, 0x06,
			0x38, 0x07, 0xE0, 0x1C, 0x0E, 0x1C, 0x38, 0x70, 0x03, 0xF0, 0x0F, 0xC0, 0x01, 0xE0, 0x07, 0x80,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		};
    }
}