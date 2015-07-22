#include "TextHelper.h"
#include "GraphicContext.h"
#include "Font.h"

#include <cstring>

PeripheralLayer::TextHelper::TextHelper(GraphicContext& context, int16_t x, int16_t y, const Fonts::Font& font, uint32_t fgcolor, uint32_t bgcolor, uint8_t size)
	: m_Context(context)
	, m_CursorX(x)
	, m_CursorY(y)
	, m_Font(font)
	, m_Fgcolor(fgcolor)
	, m_Bgcolor(bgcolor)
	, m_Size(size)
	, m_Wrap(false)
{
}

void PeripheralLayer::TextHelper::Write(uint8_t c)
{
	if (c == '\n')
	{
		m_CursorY += m_Size * m_Font.descriptor[c].height;
		m_CursorX = 0;
	}
	else if (c == '\r')
	{
		// skip em
	}
	else
	{
		m_Context.DrawChar(m_CursorX, m_CursorY, c, m_Fgcolor, m_Bgcolor, m_Font, m_Size);

		uint16_t w = m_Font.descriptor[c].width;
		uint16_t h = m_Font.descriptor[c].height;

		if (m_Font.kerning > 0 && m_Fgcolor != m_Bgcolor)
		{
			m_Context.FillRect(m_CursorX + w * m_Size, m_CursorY, m_Font.kerning * m_Size, h * m_Size, m_Bgcolor);
		}

		m_CursorX += m_Size * (w + m_Font.kerning);

		if (m_Wrap && (m_CursorX > (m_Context.Width() - m_Size * w)))
		{
			m_CursorY += m_Size * h;
			m_CursorX = 0;
		}
	}
}

void PeripheralLayer::TextHelper::Write(const char* str)
{
	for (uint16_t i = 0; i < std::strlen(str); ++i)
	{
		Write(str[i]);
	}
}

uint16_t PeripheralLayer::TextHelper::TextWidth(const char* str, uint8_t size)
{
	return std::strlen(str) * size * 6;
}

uint16_t PeripheralLayer::TextHelper::TextHeight(const char* str, uint8_t size)
{
	return size * 8;
}
