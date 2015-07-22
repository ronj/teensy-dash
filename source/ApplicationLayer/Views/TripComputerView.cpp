#include "TripComputerView.h"

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
	UpdatePagination(m_ActivePage, e);
}

void ApplicationLayer::Views::TripComputerView::UpdatePagination(uint8_t activePage, ApplicationLayer::DrawEventArgs& e)
{
	PeripheralLayer::TextHelper paginationAText(e.graphicContext, 28, 138, PeripheralLayer::Fonts::LCDFont, activePage == 0 ? e.colorScheme.Background : e.colorScheme.Text, activePage == 0 ? e.colorScheme.Text : e.colorScheme.Background, 2);
	PeripheralLayer::TextHelper paginationBText(e.graphicContext, 58, 138, PeripheralLayer::Fonts::LCDFont, activePage == 1 ? e.colorScheme.Background : e.colorScheme.Text, activePage == 1 ? e.colorScheme.Text : e.colorScheme.Background, 2);
	PeripheralLayer::TextHelper paginationCText(e.graphicContext, 87, 138, PeripheralLayer::Fonts::LCDFont, activePage == 2 ? e.colorScheme.Background : e.colorScheme.Text, activePage == 2 ? e.colorScheme.Text : e.colorScheme.Background, 2);

	uint8_t i = 0;

	for (auto x : { 32, 62, 92 })
	{
		activePage == i++ ? e.graphicContext.FillCircle(x, 145, 11, e.colorScheme.Text) :
			                e.graphicContext.DrawCircle(x, 145, 11, e.colorScheme.Text);
	}

	paginationAText.Write("A");
	paginationBText.Write("B");
	paginationCText.Write("C");

	for (auto x : { 32, 62, 92 })
	{
		e.graphicContext.DrawCircle(x, 145, 11, e.colorScheme.Text);
	}
}

void ApplicationLayer::Views::TripComputerView::UpdateTripData(uint8_t activePage, ApplicationLayer::DrawEventArgs& e)
{
	char scratchpad[50] = { 0 };

	uint32_t km = m_Model.GetTripDistance(m_ActivePage) / 1000;
	uint32_t m = (m_Model.GetTripDistance(m_ActivePage) % 1000) / 100;

	sprintf(scratchpad, "%d.%d", km, m);

	PeripheralLayer::TextHelper distanceText(e.graphicContext, e.graphicContext.Width() - PeripheralLayer::TextHelper::TextWidth(scratchpad, 3), 0 + 5, PeripheralLayer::Fonts::LCDFont, e.colorScheme.Text, e.colorScheme.Background, 3);
	distanceText.Write(scratchpad);

	uint32_t milliseconds = m_Model.GetTripTime(m_ActivePage);
	uint32_t seconds = (milliseconds / 1000) % 60;
	uint32_t minutes = (milliseconds / (1000 * 60)) % 60;
	uint32_t hours = (milliseconds / (1000 * 60 * 60));

	sprintf(scratchpad, "%d:%02d:%02d", hours, minutes, seconds);

	PeripheralLayer::TextHelper timeText(e.graphicContext, e.graphicContext.Width() - PeripheralLayer::TextHelper::TextWidth(scratchpad, 3), PeripheralLayer::TextHelper::TextHeight(scratchpad, 3) + 15, PeripheralLayer::Fonts::LCDFont, e.colorScheme.Text, e.colorScheme.Background, 3);
	timeText.Write(scratchpad);
}
