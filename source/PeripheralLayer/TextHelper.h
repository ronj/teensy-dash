#pragma once

#include <cinttypes>

namespace PeripheralLayer
{
	class GraphicContext;

	namespace Fonts
	{
		struct Font;
	}

	class TextHelper
	{
	public:
		TextHelper(GraphicContext& context, int16_t x, int16_t y, const Fonts::Font& font, uint32_t fgcolor, uint32_t bgcolor, uint8_t size);

		void Write(uint8_t c);
		void Write(const char* str);

		static uint16_t TextWidth(const char* str, uint8_t size);
		static uint16_t TextHeight(const char* str, uint8_t size);

	private:
		GraphicContext& m_Context;
		int16_t m_CursorX;
		int16_t m_CursorY;
		const Fonts::Font& m_Font;
		uint32_t m_Fgcolor;
		uint32_t m_Bgcolor;
		uint8_t m_Size;
		bool m_Wrap;
	};
}
