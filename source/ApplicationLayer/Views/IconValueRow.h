#pragma once

#include "BaseView.h"

#include <cinttypes>

namespace ApplicationLayer
{
	namespace Views
	{
		class IconValueRow : public BaseView
		{
		public:
			IconValueRow(int16_t x, int16_t y, const uint8_t* bitmap, const char* label, const Models::Model& model);

			void OnDraw(ApplicationLayer::DrawEventArgs& e);

		private:
			const uint8_t* m_Bitmap;
			const char* m_Label;
		};
	}
}
