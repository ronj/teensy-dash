#include "GraphView.h"

#include "PeripheralLayer/GraphicContext.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"

#include "ApplicationLayer/Models/Model.h"

ApplicationLayer::Views::GraphView::GraphView(int16_t x, int16_t y, int16_t width, int16_t height, const Models::Model& model)
	: BaseView(x, y, model)
	, m_Width(width)
	, m_Height(height)
	, m_XPos(0)
{
}

void ApplicationLayer::Views::GraphView::OnDraw(ApplicationLayer::DrawEventArgs& e)
{
	e.graphicContext.DrawVerticalLine(m_XPos, m_Height - GetModel().GetRawValue(), m_Height, e.colorScheme.Text);
	e.graphicContext.DrawVerticalLine(m_XPos, 0, m_Height - GetModel().GetRawValue(), e.colorScheme.Background);

	(m_XPos > m_Width) ? m_XPos = 0 : m_XPos++;
}
