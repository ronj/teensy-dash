#pragma once

#include <cinttypes>

namespace ApplicationLayer
{
	struct PaletteEntry
	{
		const uint32_t Background;
		const uint32_t Foreground;
		const uint32_t Control;
		const uint32_t Bitmap;
		const uint32_t Text;
	};

	namespace Palette {
		static const PaletteEntry Default = {
			0x363636FF,
			0x636363FF,
			0x003333FF,
			0xC3C3C3FF,
			0xFFA500FF
		};
	}
}
