#include "TripComputerView.h"

#include "PeripheralLayer/Bitmaps.h"
#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/TextHelper.h"
#include "PeripheralLayer/Fonts.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"

#include "ApplicationLayer/Models/ConversionHelper.h"
#include "ApplicationLayer/Models/TripComputerModel.h"

#include <cstdio>

ApplicationLayer::Views::TripComputerView::TripComputerView(const ApplicationLayer::Models::TripComputerModel& model)
	: m_Model(model)
	, m_Distance(0, 0, PeripheralLayer::Bitmaps::TripDistance, "KM")
	, m_AverageFuelConsumption(0, 47, PeripheralLayer::Bitmaps::FuelPump, "L/100 KM")
	, m_AverageSpeed(0, 92, PeripheralLayer::Bitmaps::AverageSpeed, "KM/H")
{
}

void ApplicationLayer::Views::TripComputerView::OnDraw(ApplicationLayer::DrawEventArgs& e)
{
	DrawTripData(m_ActivePage, e);
}

void ApplicationLayer::Views::TripComputerView::DrawTripData(uint8_t activePage, ApplicationLayer::DrawEventArgs& e)
{
	const uint8_t scratchpad_size = 16;
	char scratchpad[scratchpad_size] = { 0 };

	uint32_t km = m_Model.GetTripDistance(m_ActivePage) / 1000;
	uint32_t m = (m_Model.GetTripDistance(m_ActivePage) % 1000) / 100;
	uint32_t l_100km = m_Model.GetTripAverageFuelConsumption(m_ActivePage);

	if (km < 1000)
	{
		snprintf(scratchpad, scratchpad_size, "%lu.%lu", km, m);
	}
	else
	{
		snprintf(scratchpad, scratchpad_size, "%lu", km);
	}

	m_Distance.SetValue(scratchpad);
	m_Distance.OnDraw(e);

	snprintf(scratchpad, scratchpad_size, "%lu.%02lu", l_100km / 100,
		                                               l_100km % 100);

	m_AverageFuelConsumption.SetValue(scratchpad);
	m_AverageFuelConsumption.OnDraw(e);

	snprintf(scratchpad, scratchpad_size, "%lu", m_Model.GetTripAverageSpeed(m_ActivePage));

	m_AverageSpeed.SetValue(scratchpad);
	m_AverageSpeed.OnDraw(e);

	PeripheralLayer::TextHelper smallerFont(e.graphicContext, PeripheralLayer::Fonts::Peugeot_16pt, e.colorScheme.Text, e.colorScheme.Background);
	uint32_t milliseconds = m_Model.GetTripTime(m_ActivePage);
	uint32_t seconds = (milliseconds / 1000) % 60;
	uint32_t minutes = (milliseconds / (1000 * 60)) % 60;
	uint32_t hours = (milliseconds / (1000 * 60 * 60));

	snprintf(scratchpad, scratchpad_size, "%02lu:%02lu:%02lu", hours, minutes, seconds);

	smallerFont.SetCursor(e.graphicContext.Width() / 2 - smallerFont.TextWidth(scratchpad) / 2, e.graphicContext.Height() - smallerFont.TextHeight(scratchpad));
	smallerFont.Write(scratchpad);
}

void ApplicationLayer::Views::TripComputerView::Query()
{
}
