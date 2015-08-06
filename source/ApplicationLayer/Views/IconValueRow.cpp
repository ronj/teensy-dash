#include "IconValueRow.h"

#include "PeripheralLayer/Bitmap.h"
#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/TextHelper.h"
#include "PeripheralLayer/Fonts.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"

#include <cstring>

ApplicationLayer::Views::IconValueRow::IconValueRow(int16_t x, int16_t y, const PeripheralLayer::Bitmaps::Bitmap& bitmap, const char* label)
    : m_X(x)
    , m_Y(y)
	, m_Bitmap(bitmap)
	, m_Label(label)
{
}

void ApplicationLayer::Views::IconValueRow::SetValue(const char* value)
{
	m_Value = value;
}

void ApplicationLayer::Views::IconValueRow::OnDraw(ApplicationLayer::DrawEventArgs& e)
{
	const uint8_t xmargin = 5;
	const uint8_t ymargin = 5;

	PeripheralLayer::TextHelper valueText(e.graphicContext, PeripheralLayer::Fonts::Peugeot_20pt, e.colorScheme.Text, e.colorScheme.Background);
	PeripheralLayer::TextHelper labelText(e.graphicContext, PeripheralLayer::Fonts::Peugeot_8pt, e.colorScheme.Text, e.colorScheme.Background);

	e.graphicContext.DrawBitmap(m_X + xmargin, m_Y + ymargin, m_Bitmap, e.colorScheme.Foreground);

	valueText.SetCursor(m_X + e.graphicContext.Width() - valueText.TextWidth(m_Value) - xmargin, m_Y + ymargin);
	valueText.Write(m_Value);

	labelText.SetCursor(m_X + e.graphicContext.Width() - labelText.TextWidth(m_Label) - xmargin, m_Y + valueText.TextHeight(m_Value) + 6);
	labelText.Write(m_Label);

	e.graphicContext.DrawHorizontalLine(m_X + xmargin, m_Y + valueText.TextHeight(m_Value) + (2 * ymargin) + 2, e.graphicContext.Width() - labelText.TextWidth(m_Label) - (3 * xmargin), e.colorScheme.Foreground);
}
