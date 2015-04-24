#pragma once

#include "BaseView.h"

namespace ApplicationLayer
{
	namespace Views
	{
		class GraphView : public BaseView
		{
		public:
			GraphView(int16_t x, int16_t y, const Models::Model& model);

			void OnDraw(ApplicationLayer::DrawEventArgs& e);

		private:
			int16_t m_XPos;
		};
	}
}
