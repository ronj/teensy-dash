#pragma once

#include "BaseView.h"

#include <cinttypes>

namespace PeripheralLayer
{
	namespace Bitmaps
	{
		struct Bitmap;
	}
}

namespace ApplicationLayer
{
	namespace Views
	{
		class IconValueRow : public BaseView
		{
		public:
			IconValueRow(int16_t x, int16_t y, const PeripheralLayer::Bitmaps::Bitmap& bitmap, const char* label, const Models::Model& model);

			void OnDraw(ApplicationLayer::DrawEventArgs& e);

		private:
			const PeripheralLayer::Bitmaps::Bitmap& m_Bitmap;
			const char* m_Label;
		};
	}
}
