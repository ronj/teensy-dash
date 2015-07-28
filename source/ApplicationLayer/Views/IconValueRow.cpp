#include "IconValueRow.h"

#include "PeripheralLayer/Bitmap.h"
#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/TextHelper.h"
#include "PeripheralLayer/Fonts.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"

#include "ApplicationLayer/Models/Model.h"

#include "Common/Logger.h"

#include <cstring>

ApplicationLayer::Views::IconValueRow::IconValueRow(int16_t x, int16_t y, const PeripheralLayer::Bitmaps::Bitmap& bitmap, const char* label, const Models::Model& model)
	: BaseView(x, y, model)
	, m_Bitmap(bitmap)
	, m_Label(label)
{
}

void ApplicationLayer::Views::IconValueRow::OnDraw(ApplicationLayer::DrawEventArgs& e)
{
	const uint8_t xmargin = 5;
	const uint8_t ymargin = 5;

	e.graphicContext.DrawBitmap(GetX() + xmargin, GetY() + ymargin, m_Bitmap, e.colorScheme.Foreground);

	PeripheralLayer::TextHelper valueText(e.graphicContext, PeripheralLayer::Fonts::Peugeot_20pt, e.colorScheme.Text, e.colorScheme.Background);

	valueText.SetCursor(GetX() + 32 + 15, GetY() + 12);
	valueText.Write(GetModel().GetFormattedValue());

	PeripheralLayer::TextHelper labelText(e.graphicContext, PeripheralLayer::Fonts::LCDFont, e.colorScheme.Text, e.colorScheme.Background);

	labelText.SetCursor(e.graphicContext.Width() - 10 - std::strlen(m_Label) * 8 + 10, GetY() + 32 + 5 + 2);
	labelText.Write(m_Label);

	e.graphicContext.DrawHorizontalLine(GetX() + 5, GetY() + 32 + 5 + 5, e.graphicContext.Width() - 10 - std::strlen(m_Label) * 8, e.colorScheme.Foreground);
}
