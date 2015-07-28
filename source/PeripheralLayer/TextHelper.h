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
		TextHelper(GraphicContext& context, const Fonts::Font& font, uint32_t foreground, uint32_t background);
		TextHelper(GraphicContext& context, const Fonts::Font& font, uint32_t foreground, uint32_t background, uint8_t scaling);

		void SetCursor(int16_t x, int16_t y);

		void Write(uint8_t c);
		void Write(const char* str);

		uint16_t TextWidth(const char* str) const;
		uint16_t TextHeight(const char* str) const;

	private:
		GraphicContext& m_Context;
		const Fonts::Font& m_Font;

		int16_t m_CursorX = 0;
		int16_t m_CursorY = 0;
		uint32_t m_Foreground = 0;
		uint32_t m_Background = 0;
		const uint8_t m_Scaling = 1;
		bool m_Wrap = false;
	};
}
