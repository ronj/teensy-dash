#pragma once

#include "BaseView.h"

namespace ApplicationLayer
{
	namespace Views
	{
		class GraphView : public BaseView
		{
		public:
			GraphView(int16_t x, int16_t y, int16_t width, int16_t height, const Models::Model& model);

			void OnDraw(ApplicationLayer::DrawEventArgs& e);

		private:
			int16_t m_Width;
			int16_t m_Height;
			int16_t m_XPos;
		};
	}
}
