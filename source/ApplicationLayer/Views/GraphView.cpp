#include "GraphView.h"

#include "PeripheralLayer/GraphicContext.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"

#include "ApplicationLayer/Models/Model.h"

ApplicationLayer::Views::GraphView::GraphView(int16_t x, int16_t y, const Models::Model& model)
	: BaseView(x, y, model)
	, m_XPos(0)
{
}

void ApplicationLayer::Views::GraphView::OnDraw(ApplicationLayer::DrawEventArgs& e)
{
	e.graphicContext.DrawVerticalLine(m_XPos, 160 - GetModel().GetRawValue(), 160, e.colorScheme.Control);

	(m_XPos > 128) ? m_XPos = 0 : m_XPos++;
}
