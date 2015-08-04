#pragma once

#include "BaseView.h"

#include <cinttypes>

namespace ApplicationLayer
{
	namespace Views
	{
		class LargeValueView : public BaseView
		{
		public:
			LargeValueView(int16_t x, int16_t y, const char* label, const Models::Model& model);

			void OnDraw(ApplicationLayer::DrawEventArgs& e);
			void Query();

		private:
			const char* m_Label;
		};
	}
}
