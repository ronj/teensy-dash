#include "XYScatterView.h"

#include "Common/Interpolation.h"
#include "Common/Math.h"

#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/Color.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"

#include "ApplicationLayer/Models/Model.h"

#include <algorithm>

ApplicationLayer::Views::XYScatterView::XYScatterView(int16_t, int16_t, const Models::Model& xModel, const Models::Model& yModel)
    : m_XModel(xModel)
    , m_YModel(yModel)
{
}

void ApplicationLayer::Views::XYScatterView::OnDraw(ApplicationLayer::DrawEventArgs& e)
{
	for (auto&& point : m_Trail)
	{
		e.graphicContext.FillCircle(point.x, point.y, 5, e.colorScheme.Background);
	}

    e.graphicContext.DrawVerticalLine(e.graphicContext.Width() / 2, 0, e.graphicContext.Height(), e.colorScheme.Foreground);
	e.graphicContext.DrawHorizontalLine(0, e.graphicContext.Height() / 2, e.graphicContext.Width(), e.colorScheme.Foreground);

	std::rotate(m_Trail.begin(), m_Trail.begin() + 1, m_Trail.end());

	m_Trail[0].x = Common::Math::Map(m_XModel.GetRawValue(), -1000, 1000, 0, e.graphicContext.Width());
	m_Trail[0].y = Common::Math::Map(m_YModel.GetRawValue(), -1000, 1000, 0, e.graphicContext.Height());

	float step = 0;
	float stepSize = 1.0f / m_Trail.size();

	PeripheralLayer::Color::RGB beginColor(e.colorScheme.Text);
	PeripheralLayer::Color::RGB endColor(e.colorScheme.Background);

	for (auto&& point : m_Trail)
	{
		PeripheralLayer::Color::RGB currentColor = PeripheralLayer::Color::Interpolate(beginColor, endColor, step, &Common::Interpolation::Linear<int>);
		step += stepSize;

		e.graphicContext.FillCircle(point.x, point.y, 5, currentColor.ToRGBA(0xFF));
	}
}
