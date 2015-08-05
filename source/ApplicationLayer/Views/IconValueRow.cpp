#include "IconValueRow.h"

#include "PeripheralLayer/Bitmap.h"
#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/TextHelper.h"
#include "PeripheralLayer/Fonts.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"

#include "ApplicationLayer/Models/Model.h"

#include <cstring>

ApplicationLayer::Views::IconValueRow::IconValueRow(int16_t x, int16_t y, const PeripheralLayer::Bitmaps::Bitmap& bitmap, const char* label, const Models::Model& model)
	: BaseView(x, y, model)
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

	const char* value = GetModel().GetFormattedValue();

	PeripheralLayer::TextHelper valueText(e.graphicContext, PeripheralLayer::Fonts::Peugeot_20pt, e.colorScheme.Text, e.colorScheme.Background);
	PeripheralLayer::TextHelper labelText(e.graphicContext, PeripheralLayer::Fonts::Peugeot_8pt, e.colorScheme.Text, e.colorScheme.Background);

	e.graphicContext.DrawBitmap(GetX() + xmargin, GetY() + ymargin, m_Bitmap, e.colorScheme.Foreground);

	valueText.SetCursor(e.graphicContext.Width() - valueText.TextWidth(value) - xmargin, 0 + ymargin);
	valueText.Write(value);

	labelText.SetCursor(e.graphicContext.Width() - labelText.TextWidth(m_Label) - xmargin, valueText.TextHeight(value) + 6);
	labelText.Write(m_Label);

	e.graphicContext.DrawHorizontalLine(0 + xmargin, 0 + valueText.TextHeight(value) + (2 * ymargin), e.graphicContext.Width() - labelText.TextWidth(m_Label) - (3 * xmargin), e.colorScheme.Foreground);
}
