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
	char scratchpad[15] = { 0 };

	uint32_t km = m_Model.GetTripDistance(m_ActivePage) / 1000;
	uint32_t m = (m_Model.GetTripDistance(m_ActivePage) % 1000) / 100;

	if (km < 1000)
	{
		sprintf(scratchpad, "%lu.%lu", km, m);
	}
	else
	{
		sprintf(scratchpad, "%lu", km);
	}

	m_Distance.SetValue(scratchpad);
	m_Distance.OnDraw(e);

	sprintf(scratchpad, "%lu.%lu", m_Model.GetTripAverageFuelConsumption(m_ActivePage) / 100,
		                           m_Model.GetTripAverageFuelConsumption(m_ActivePage) % 100);

	m_AverageFuelConsumption.SetValue(scratchpad);
	m_AverageFuelConsumption.OnDraw(e);

	sprintf(scratchpad, "%lu", m_Model.GetTripAverageSpeed(m_ActivePage));

	m_AverageSpeed.SetValue(scratchpad);
	m_AverageSpeed.OnDraw(e);

	PeripheralLayer::TextHelper smallerFont(e.graphicContext, PeripheralLayer::Fonts::Peugeot_16pt, e.colorScheme.Text, e.colorScheme.Background);
	uint32_t milliseconds = m_Model.GetTripTime(m_ActivePage);
	uint32_t seconds = (milliseconds / 1000) % 60;
	uint32_t minutes = (milliseconds / (1000 * 60)) % 60;
	uint32_t hours = (milliseconds / (1000 * 60 * 60));

	sprintf(scratchpad, "%02lu:%02lu:%02lu", hours, minutes, seconds);

	smallerFont.SetCursor(e.graphicContext.Width() / 2 - smallerFont.TextWidth(scratchpad) / 2, e.graphicContext.Height() - smallerFont.TextHeight(scratchpad));
	smallerFont.Write(scratchpad);
}

void ApplicationLayer::Views::TripComputerView::Query()
{
}
