#include "TwoRowView.h"

#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/TextHelper.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"
#include "ApplicationLayer/Fonts.h"

#include "ApplicationLayer/Models/Model.h"

#include <cstring>

ApplicationLayer::Views::TwoRowView::TwoRowView(int16_t x, int16_t y, const char* labelOne, const Models::Model& modelOne,
	                                                                  const char* labelTwo, const Models::Model& modelTwo)
	: m_X(x)
	, m_Y(y)
	, m_LabelOne(labelOne)
	, m_ModelOne(modelOne)
	, m_LabelTwo(labelTwo)
	, m_ModelTwo(modelTwo)
{
}

void ApplicationLayer::Views::TwoRowView::OnDraw(ApplicationLayer::DrawEventArgs& e)
{
	DrawLabelAndModel(m_X, m_Y, e, m_LabelOne, m_ModelOne, m_PreviousWidthOne);
	DrawLabelAndModel(m_X, m_Y + e.graphicContext.Height() / 2, e, m_LabelTwo, m_ModelTwo, m_PreviousWidthTwo);
}

void ApplicationLayer::Views::TwoRowView::DrawLabelAndModel(int16_t x, int16_t y, ApplicationLayer::DrawEventArgs& e, const char* label, const Models::Model& model, uint16_t& previousWidth)
{
	const uint8_t textSize = 7;
	const uint8_t labelSize = 2;

	const char* value = model.GetFormattedValue();
	uint16_t textWidthValue = PeripheralLayer::TextHelper::TextWidth(value, textSize);

	int16_t xposValue = e.graphicContext.Width() / 2 - textWidthValue / 2 + x + 3;
	int16_t xposLabel = e.graphicContext.Width() / 2 - PeripheralLayer::TextHelper::TextWidth(label, labelSize) / 2 + x;

	if (textWidthValue < previousWidth)
	{
		e.graphicContext.FillRect(x, y + 10, e.graphicContext.Width(), PeripheralLayer::TextHelper::TextHeight(value, textSize), e.colorScheme.Background);
	}
	previousWidth = textWidthValue;

	PeripheralLayer::TextHelper valueText(e.graphicContext, xposValue, y + 10, Fonts::LCDFont, e.colorScheme.Text, e.colorScheme.Background, textSize);
	valueText.Write(value);

	PeripheralLayer::TextHelper labelText(e.graphicContext, xposLabel, y + 15 + PeripheralLayer::TextHelper::TextHeight(value, textSize), Fonts::LCDFont, e.colorScheme.Text, e.colorScheme.Background, labelSize);
	labelText.Write(label);
}
