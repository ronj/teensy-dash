#include "TextHelper.h"
#include "GraphicContext.h"

#include <cstring>

PeripheralLayer::TextHelper::TextHelper(GraphicContext& context, int16_t x, int16_t y, const uint8_t* font, uint32_t fgcolor, uint32_t bgcolor, uint8_t size)
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
		m_CursorY += m_Size * 8;
		m_CursorX = 0;
	}
	else if (c == '\r')
	{
		// skip em
	}
	else
	{
		m_Context.DrawChar(m_CursorX, m_CursorY, c, m_Fgcolor, m_Bgcolor, m_Font, m_Size);
		m_CursorX += m_Size * 6;
		if (m_Wrap && (m_CursorX > (m_Context.Width() - m_Size * 6))) {
			m_CursorY += m_Size * 8;
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
