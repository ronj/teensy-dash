#include "LargeValueView.h"

#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/TextHelper.h"
#include "PeripheralLayer/Fonts.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"

#include "ApplicationLayer/Models/Model.h"

ApplicationLayer::Views::LargeValueView::LargeValueView(int16_t x, int16_t y, const char* label, const Models::Model& model)
	: BaseView(x, y, model)
	, m_Label(label)
{
}

void ApplicationLayer::Views::LargeValueView::OnDraw(ApplicationLayer::DrawEventArgs& e)
{
	const uint8_t textSize = 12;
	const uint8_t labelSize = 3;

	int16_t xpos = e.graphicContext.Width() / 2 - (textSize * 3) + 5;

	PeripheralLayer::TextHelper valueText(e.graphicContext, PeripheralLayer::Fonts::LCDFont, e.colorScheme.Text, e.colorScheme.Background, textSize);

	valueText.SetCursor(xpos, GetY() + 15);
	valueText.Write(GetModel().GetFormattedValue());

	PeripheralLayer::TextHelper labelText(e.graphicContext, PeripheralLayer::Fonts::LCDFont, e.colorScheme.Text, e.colorScheme.Background, labelSize);

	labelText.SetCursor(xpos, GetY() + 15 + 10 + textSize * 8);
	labelText.Write(m_Label);
}
