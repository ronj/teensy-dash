#include "TripComputerView.h"

#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/TextHelper.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"
#include "ApplicationLayer/Fonts.h"

#include "ApplicationLayer/Models/TripComputerModel.h"

ApplicationLayer::Views::TripComputerView::TripComputerView(const ApplicationLayer::Models::TripComputerModel& model)
	: m_Model(model)
{
}

void ApplicationLayer::Views::TripComputerView::OnDraw(ApplicationLayer::DrawEventArgs& e)
{
	PeripheralLayer::TextHelper valueText(e.graphicContext, 0 + 5, 0 + 5, Fonts::LCDFont, e.colorScheme.Text, e.colorScheme.Background, 3);

	valueText.Write(m_Model.GetFormattedValue());
}
