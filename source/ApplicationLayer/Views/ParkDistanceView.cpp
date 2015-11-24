#include "ParkDistanceView.h"

#include "Common/Logger.h"

#include "PeripheralLayer/Bitmaps.h"
#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/TextHelper.h"
#include "PeripheralLayer/Fonts.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"

#include "ApplicationLayer/Models/ParkDistanceModel.h"

#include <algorithm>

ApplicationLayer::Views::ParkDistanceView::ParkDistanceView(const Models::RepresentableModel& model)
	: m_Model(model)
{
}

void ApplicationLayer::Views::ParkDistanceView::OnDraw(ApplicationLayer::DrawEventArgs& e)
{
	const uint16_t xmargin = 5;
	const uint16_t ymargin = 5;
	const uint16_t halfWidth = e.graphicContext.Width() / 2;

	int32_t packedValue = m_Model.GetRawValue();

	e.graphicContext.DrawBitmap(e.graphicContext.Width() / 2 - PeripheralLayer::Bitmaps::BigCar.width / 2, ymargin, PeripheralLayer::Bitmaps::BigCar, e.colorScheme.Foreground);

	const char* distance = m_Model.GetFormattedValue();

	PeripheralLayer::TextHelper distanceText(e.graphicContext, PeripheralLayer::Fonts::Peugeot_20pt, e.colorScheme.Text, e.colorScheme.Background);
	distanceText.SetCursor(halfWidth - distanceText.TextWidth(distance) / 2, e.graphicContext.Height() - (ymargin + distanceText.TextHeight(distance)));
	distanceText.Write(distance);
}

void ApplicationLayer::Views::ParkDistanceView::Query()
{
	Common::Logger::Get().LogExpectation(m_Model.GetRawValue());
}
