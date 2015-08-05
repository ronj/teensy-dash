#include "TripComputerView.h"

#include "PeripheralLayer/Bitmaps.h"
#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/TextHelper.h"
#include "PeripheralLayer/Fonts.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"

#include "ApplicationLayer/Models/TripComputerModel.h"

#include <initializer_list>
#include <cstdio>

ApplicationLayer::Views::TripComputerView::TripComputerView(const ApplicationLayer::Models::TripComputerModel& model)
	: m_Model(model)
{
}

void ApplicationLayer::Views::TripComputerView::OnDraw(ApplicationLayer::DrawEventArgs& e)
{
	UpdateTripData(m_ActivePage, e);
}

void ApplicationLayer::Views::TripComputerView::UpdateTripData(uint8_t activePage, ApplicationLayer::DrawEventArgs& e)
{
	char scratchpad[15] = { 0 };

	const uint8_t xmargin = 5;
	const uint8_t ymargin = 5;

	PeripheralLayer::TextHelper valueText(e.graphicContext, PeripheralLayer::Fonts::Peugeot_20pt, e.colorScheme.Text, e.colorScheme.Background);
	PeripheralLayer::TextHelper labelText(e.graphicContext, PeripheralLayer::Fonts::Peugeot_8pt, e.colorScheme.Text, e.colorScheme.Background);

	uint32_t km = m_Model.GetTripDistance(m_ActivePage) / 1000;
	uint32_t m = (m_Model.GetTripDistance(m_ActivePage) % 1000) / 100;

	sprintf(scratchpad, "%lu.%lu", km, m);

	e.graphicContext.DrawBitmap(0 + xmargin, 0 + ymargin, PeripheralLayer::Bitmaps::TripDistance, e.colorScheme.Foreground);

	valueText.SetCursor(e.graphicContext.Width() - valueText.TextWidth(scratchpad) - xmargin, 0 + ymargin);
	valueText.Write(scratchpad);

	labelText.SetCursor(e.graphicContext.Width() - labelText.TextWidth("KM") - xmargin, valueText.TextHeight(scratchpad) + 6);
	labelText.Write("KM");

	e.graphicContext.DrawHorizontalLine(0 + xmargin, 0 + valueText.TextHeight(scratchpad) + (2 * ymargin), e.graphicContext.Width() - labelText.TextWidth("KM") - (3 * xmargin), e.colorScheme.Foreground);


	sprintf(scratchpad, "5.87");

	e.graphicContext.DrawBitmap(0 + xmargin, 40 + ymargin, PeripheralLayer::Bitmaps::FuelPump, e.colorScheme.Foreground);

	valueText.SetCursor(e.graphicContext.Width() - valueText.TextWidth(scratchpad) - xmargin, 45 + ymargin);
	valueText.Write(scratchpad);

	labelText.SetCursor(e.graphicContext.Width() - labelText.TextWidth("L/100 KM") - xmargin, 45 + valueText.TextHeight(scratchpad) + 6);
	labelText.Write("L/100 KM");

	e.graphicContext.DrawHorizontalLine(0 + xmargin, 45 + valueText.TextHeight(scratchpad) + (2 * ymargin), e.graphicContext.Width() - labelText.TextWidth("L/100 KM") - (3 * xmargin), e.colorScheme.Foreground);


	sprintf(scratchpad, "%lu", m_Model.GetTripAverageSpeed(m_ActivePage));

	e.graphicContext.DrawBitmap(0 + xmargin, 85 + ymargin, PeripheralLayer::Bitmaps::AverageSpeed, e.colorScheme.Foreground);

	valueText.SetCursor(e.graphicContext.Width() - valueText.TextWidth(scratchpad) - xmargin, 90 + ymargin);
	valueText.Write(scratchpad);

	labelText.SetCursor(e.graphicContext.Width() - labelText.TextWidth("KM/H") - xmargin, 90 + valueText.TextHeight(scratchpad) + 6);
	labelText.Write("KM/H");

	e.graphicContext.DrawHorizontalLine(0 + xmargin, 90 + valueText.TextHeight(scratchpad) + (2 * ymargin), e.graphicContext.Width() - labelText.TextWidth("KM/H") - (3 * xmargin), e.colorScheme.Foreground);


	PeripheralLayer::TextHelper smallerFont(e.graphicContext, PeripheralLayer::Fonts::Peugeot_16pt, e.colorScheme.Text, e.colorScheme.Background);
	uint32_t milliseconds = m_Model.GetTripTime(m_ActivePage);
	uint32_t seconds = (milliseconds / 1000) % 60;
	uint32_t minutes = (milliseconds / (1000 * 60)) % 60;
	uint32_t hours = (milliseconds / (1000 * 60 * 60));

	sprintf(scratchpad, "%02lu:%02lu:%02lu", hours, minutes, seconds);

	smallerFont.SetCursor(e.graphicContext.Width() / 2 - smallerFont.TextWidth(scratchpad) / 2 + 1, e.graphicContext.Height() - smallerFont.TextHeight(scratchpad));
	smallerFont.Write(scratchpad);
}

void ApplicationLayer::Views::TripComputerView::Query()
{
}
