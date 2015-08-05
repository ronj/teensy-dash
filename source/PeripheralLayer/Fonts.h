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

			extern const uint8_t peugeotExpandedMedium_20pt_Data[];
			extern const Descriptor peugeotExpandedMedium_20pt_Descriptor[];

			extern const uint8_t peugeotExpandedMedium_16pt_Data[];
			extern const Descriptor peugeotExpandedMedium_16pt_Descriptor[];

			extern const uint8_t peugeotExpandedMedium_8pt_Data[];
			extern const Descriptor peugeotExpandedMedium_8pt_Descriptor[];
		}

		static const Font LCDFont = { 0x00, 0xFF, 1, internal::GLCDFont_Descriptor, internal::GLCDFont_Data };

		static const Font Peugeot_20pt = { '+', '>', 1, internal::peugeotExpandedMedium_20pt_Descriptor, internal::peugeotExpandedMedium_20pt_Data };
		static const Font Peugeot_16pt = { '+', '>', 1, internal::peugeotExpandedMedium_16pt_Descriptor, internal::peugeotExpandedMedium_16pt_Data };
		static const Font Peugeot_8pt = { ' ', '~', 1, internal::peugeotExpandedMedium_8pt_Descriptor, internal::peugeotExpandedMedium_8pt_Data };
	}
}
