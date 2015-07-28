#include "TextHelper.h"
#include "GraphicContext.h"
#include "Font.h"

#include <cstring>

PeripheralLayer::TextHelper::TextHelper(GraphicContext& context, const Fonts::Font& font, uint32_t foreground, uint32_t background)
	: TextHelper(context, font, foreground, background, 1)
{
}

PeripheralLayer::TextHelper::TextHelper(GraphicContext& context, const Fonts::Font& font, uint32_t foreground, uint32_t background, uint8_t scaling)
	: m_Context(context)
	, m_Font(font)
	, m_Foreground(foreground)
	, m_Background(background)
	, m_Scaling(scaling)
{
}

void PeripheralLayer::TextHelper::SetCursor(int16_t x, int16_t y)
{
	m_CursorX = x;
	m_CursorY = y;
}

void PeripheralLayer::TextHelper::Write(uint8_t c)
{
	if (c == '\n')
	{
		m_CursorY += m_Scaling * m_Font.descriptor[c].height;
		m_CursorX = 0;
	}
	else if (c == '\r')
	{
		// skip em
	}
	else
	{
		if (c < m_Font.StartCharacter() || c > m_Font.EndCharacter())
		{
			c = 0;
		}
		else
		{
			c -= m_Font.StartCharacter();
		}

		m_Context.DrawChar(m_CursorX, m_CursorY, c, m_Foreground, m_Background, m_Font, m_Scaling);

		uint16_t w = m_Font.descriptor[c].width;
		uint16_t h = m_Font.descriptor[c].height;

		if (m_Font.kerning > 0 && m_Foreground != m_Background)
		{
			m_Context.FillRect(m_CursorX + w * m_Scaling, m_CursorY, m_Font.kerning * m_Scaling, h * m_Scaling, m_Background);
		}

		m_CursorX += m_Scaling * (w + m_Font.kerning);

		if (m_Wrap && (m_CursorX > (m_Context.Width() - m_Scaling * w)))
		{
			m_CursorY += m_Scaling * h;
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

uint16_t PeripheralLayer::TextHelper::TextWidth(const char* str) const
{
	uint16_t width = 0;

	for (uint16_t i = 0; i < std::strlen(str); ++i)
	{
		width += (m_Font.descriptor[str[i] - m_Font.startCharacter].width + m_Font.kerning) * m_Scaling;
	}

	return width;
}

uint16_t PeripheralLayer::TextHelper::TextHeight(const char* str) const
{
	return m_Font.descriptor[str[0] - m_Font.startCharacter].height * m_Scaling;
}
