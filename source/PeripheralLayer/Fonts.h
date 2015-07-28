#pragma once

#include "Font.h"

namespace PeripheralLayer
{
	namespace Fonts
	{
		namespace internal
		{
			extern const uint8_t GLCDFont_Data[];
			extern const Descriptor GLCDFont_Descriptor[];

			extern const uint8_t Peugeot_20pt_Data[];
			extern const Descriptor Peugeot_20pt_Descriptor[];

			extern const uint8_t peugeot_16pt_Data[];
			extern const Descriptor peugeot_16pt_Descriptor[];

			extern const uint8_t peugeot_8pt_Data[];
			extern const Descriptor peugeot_8pt_Descriptor[];
		}

		static const Font LCDFont = { 0x00, 0xFF, 1, internal::GLCDFont_Descriptor, internal::GLCDFont_Data };

		static const Font Peugeot_20pt = { ',', ':', 1, internal::Peugeot_20pt_Descriptor, internal::Peugeot_20pt_Data };
		static const Font peugeot_18pt = { ',', ':', 1, internal::peugeot_16pt_Descriptor, internal::peugeot_16pt_Data };
		static const Font peugeot_8pt = { ' ', '~', 1, internal::peugeot_8pt_Descriptor, internal::peugeot_8pt_Data };
	}
}
