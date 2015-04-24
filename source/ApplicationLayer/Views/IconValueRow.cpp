#include "IconValueRow.h"

#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/TextHelper.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"
#include "ApplicationLayer/Fonts.h"
#include "ApplicationLayer/Images.h"

#include "ApplicationLayer/Models/Model.h"

#include "Common/Logger.h"

#include <cstring>

ApplicationLayer::Views::IconValueRow::IconValueRow(int16_t x, int16_t y, const uint8_t* bitmap, const char* label, const Models::Model& model)
	: BaseView(x, y, model)
	, m_Bitmap(bitmap)
	, m_Label(label)
{
}

void ApplicationLayer::Views::IconValueRow::OnDraw(ApplicationLayer::DrawEventArgs& e)
{
	const uint8_t xmargin = 5;
	const uint8_t ymargin = 5;

	e.graphicContext.DrawBitmap(GetX() + xmargin, GetY() + ymargin, m_Bitmap, 32, 32, e.colorScheme.Foreground);

	PeripheralLayer::TextHelper valueText(e.graphicContext, GetX() + 32 + 15, GetY() + 12, Fonts::LCDFont, e.colorScheme.Text, e.colorScheme.Background, 3);

	valueText.Write(GetModel().GetFormattedValue());

	PeripheralLayer::TextHelper labelText(e.graphicContext, e.graphicContext.Width() - 10 - std::strlen(m_Label) * 8 + 10, GetY() + 32 + 5 + 2, Fonts::LCDFont, e.colorScheme.Text, e.colorScheme.Background, 1);
	labelText.Write(m_Label);

	e.graphicContext.DrawHorizontalLine(GetX() + 5, GetY() + 32 + 5 + 5, e.graphicContext.Width() - 10 - std::strlen(m_Label) * 8, e.colorScheme.Foreground);

	Common::Logger::Get().LogExpectation(GetModel().GetRawValue());
}
