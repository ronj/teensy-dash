#include "ParkDistanceView.h"

#include "PeripheralLayer/Bitmaps.h"
#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/TextHelper.h"
#include "PeripheralLayer/Fonts.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"

#include "ApplicationLayer/Models/ParkDistanceModel.h"

#include <algorithm>

ApplicationLayer::Views::ParkDistanceView::ParkDistanceView(const Models::ParkDistanceModel& model)
	: m_Model(model)
{
}

void ApplicationLayer::Views::ParkDistanceView::OnDraw(ApplicationLayer::DrawEventArgs& e)
{
	const uint16_t xmargin = 5;
	const uint16_t ymargin = 5;

	e.graphicContext.FillScreen(e.colorScheme.Background);
	e.graphicContext.DrawBitmap(e.graphicContext.Width() / 2 - PeripheralLayer::Bitmaps::BigCar.width / 2, ymargin, PeripheralLayer::Bitmaps::BigCar, e.colorScheme.Foreground);

	const uint16_t halfWidth = e.graphicContext.Width() / 2;
	const uint16_t baseWidth = PeripheralLayer::Bitmaps::BigCar.width + 15;
	const uint16_t segmentWidth = (baseWidth * 2) / 4;
	const uint16_t segmentHeight = e.graphicContext.Height() - (PeripheralLayer::Bitmaps::BigCar.height + 2 * ymargin) / 4;

	PeripheralLayer::Point leftmost[] = { { static_cast<int16_t>(halfWidth - baseWidth), static_cast<int16_t>(e.graphicContext.Height() - ymargin) },
										  { static_cast<int16_t>(halfWidth - baseWidth + segmentWidth), static_cast<int16_t>(e.graphicContext.Height() - ymargin) },
										  { static_cast<int16_t>(halfWidth - baseWidth + (segmentWidth * 1.5f)), static_cast<int16_t>(PeripheralLayer::Bitmaps::BigCar.height + ymargin * 2) },
										  { static_cast<int16_t>(halfWidth - baseWidth + segmentWidth), static_cast<int16_t>(PeripheralLayer::Bitmaps::BigCar.height + ymargin * 2) }
	};

	PeripheralLayer::Point centerleft[] = { { static_cast<int16_t>(halfWidth - baseWidth + segmentWidth + xmargin), static_cast<int16_t>(e.graphicContext.Height() - ymargin) },
										    { static_cast<int16_t>(halfWidth - xmargin / 2), static_cast<int16_t>(e.graphicContext.Height() - ymargin) },
										    { static_cast<int16_t>(halfWidth - xmargin / 2), static_cast<int16_t>(PeripheralLayer::Bitmaps::BigCar.height + ymargin * 2) },
										    { static_cast<int16_t>(halfWidth - baseWidth + (segmentWidth * 1.5f) + xmargin), static_cast<int16_t>(PeripheralLayer::Bitmaps::BigCar.height + ymargin * 2) }
	};

	PeripheralLayer::Point centerright[] = { { static_cast<int16_t>(halfWidth + baseWidth), static_cast<int16_t>(e.graphicContext.Height() - ymargin) },
										     { static_cast<int16_t>(halfWidth + baseWidth - segmentWidth), static_cast<int16_t>(e.graphicContext.Height() - ymargin) },
										     { static_cast<int16_t>(halfWidth + baseWidth - (segmentWidth * 1.5f)), static_cast<int16_t>(PeripheralLayer::Bitmaps::BigCar.height + ymargin * 2) },
										     { static_cast<int16_t>(halfWidth + baseWidth - segmentWidth), static_cast<int16_t>(PeripheralLayer::Bitmaps::BigCar.height + ymargin * 2) }
	};

	PeripheralLayer::Point rightmost[] = { { static_cast<int16_t>(halfWidth + baseWidth - segmentWidth - xmargin), static_cast<int16_t>(e.graphicContext.Height() - ymargin) },
										   { static_cast<int16_t>(halfWidth + xmargin / 2), static_cast<int16_t>(e.graphicContext.Height() - ymargin) },
										   { static_cast<int16_t>(halfWidth + xmargin / 2), static_cast<int16_t>(PeripheralLayer::Bitmaps::BigCar.height + ymargin * 2) },
										   { static_cast<int16_t>(halfWidth + baseWidth - 1.5 * segmentWidth - xmargin), static_cast<int16_t>(PeripheralLayer::Bitmaps::BigCar.height + ymargin * 2) }
	};

	uint8_t a, b, c, d;
	Models::ParkDistanceModel::UnpackValues(m_Model.GetRawValue(), a, b, c, d);
	uint8_t min = std::min({ a, b, c, d });

	if (min == a) e.graphicContext.DrawPolygon(leftmost, 4, 0xFF000000);
	if (min == b) e.graphicContext.DrawPolygon(centerleft, 4, 0xFF000000);
	if (min == c) e.graphicContext.DrawPolygon(centerright, 4, 0xFF000000);
	if (min == d) e.graphicContext.DrawPolygon(rightmost, 4, 0xFF000000);

	const char* distance = m_Model.GetFormattedValue();

	PeripheralLayer::TextHelper distanceText(e.graphicContext, PeripheralLayer::Fonts::Peugeot_20pt, e.colorScheme.Text);
	distanceText.SetCursor(halfWidth - distanceText.TextWidth(distance) / 2, e.graphicContext.Height() - (ymargin + distanceText.TextHeight(distance)));
	distanceText.Write(distance);
}

void ApplicationLayer::Views::ParkDistanceView::Query()
{
}
