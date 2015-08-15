#include "TwoRowView.h"

#include "Common/Logger.h"

#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/TextHelper.h"
#include "PeripheralLayer/Fonts.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"

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
	DrawLabelAndModel(m_X, m_Y, e, m_LabelOne, m_ModelOne, 7, m_PreviousWidthOne);
	DrawLabelAndModel(m_X, m_Y + e.graphicContext.Height() / 2 + 10, e, m_LabelTwo, m_ModelTwo, 5, m_PreviousWidthTwo);
}

void ApplicationLayer::Views::TwoRowView::Query()
{
	Common::Logger::Get().LogExpectation(m_ModelOne.GetRawValue());
}

void ApplicationLayer::Views::TwoRowView::DrawLabelAndModel(int16_t x, int16_t y, ApplicationLayer::DrawEventArgs& e, const char* label, const Models::Model& model, uint8_t textSize, uint16_t& previousWidth)
{
	const uint8_t labelSize = 2;

	PeripheralLayer::TextHelper valueText(e.graphicContext, PeripheralLayer::Fonts::LCDFont, e.colorScheme.Text, e.colorScheme.Background, textSize);
	PeripheralLayer::TextHelper labelText(e.graphicContext, PeripheralLayer::Fonts::LCDFont, e.colorScheme.Text, e.colorScheme.Background, labelSize);

	const char* value = model.GetFormattedValue();
	uint16_t textWidthValue = valueText.TextWidth(value);

	int16_t xposValue = e.graphicContext.Width() / 2 - textWidthValue / 2 + x + 3;
	int16_t xposLabel = e.graphicContext.Width() / 2 - labelText.TextWidth(label) / 2 + x;

	if (textWidthValue < previousWidth)
	{
		e.graphicContext.FillRect(x, y + 10, e.graphicContext.Width(), valueText.TextHeight(value), e.colorScheme.Background);
	}
	previousWidth = textWidthValue;

	valueText.SetCursor(xposValue, y + 10);
	valueText.Write(value);

	labelText.SetCursor(xposLabel, y + 15 + valueText.TextHeight(value));
	labelText.Write(label);
}
