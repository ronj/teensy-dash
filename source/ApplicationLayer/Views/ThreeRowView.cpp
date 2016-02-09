#include "ThreeRowView.h"

#include "PeripheralLayer/Bitmaps.h"
#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/TextHelper.h"
#include "PeripheralLayer/Fonts.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"

#include "ApplicationLayer/Models/ConversionHelper.h"
#include "ApplicationLayer/Models/RepresentableModel.h"

#include <cstdio>
#include <cinttypes>

ApplicationLayer::Views::ThreeRowView::ThreeRowView(const ApplicationLayer::Models::RepresentableModel& model)
	: m_Model(model)
	, m_RowOne(0, 0, PeripheralLayer::Bitmaps::Battery, "Volt")
	, m_RowTwo(0, 47, PeripheralLayer::Bitmaps::FuelPump, "L/100 KM")
	, m_RowThree(0, 92, PeripheralLayer::Bitmaps::AverageSpeed, "KM/H")
{
}

void ApplicationLayer::Views::ThreeRowView::OnDraw(ApplicationLayer::DrawEventArgs& e)
{
	m_RowOne.SetValue(m_Model.GetFormattedValue());
	m_RowOne.OnDraw(e);
}

void ApplicationLayer::Views::ThreeRowView::Query()
{
}
