#pragma once

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
	class DrawEventArgs;

	namespace Views
	{
		class IconValueRow
		{
		public:
			IconValueRow(int16_t x, int16_t y, const PeripheralLayer::Bitmaps::Bitmap& bitmap, const char* label);

			void SetValue(const char* value);

			void OnDraw(ApplicationLayer::DrawEventArgs& e);

		private:
			int16_t m_X;
			int16_t m_Y;

			const PeripheralLayer::Bitmaps::Bitmap& m_Bitmap;

			const char* m_Label;
			const char* m_Value;
		};
	}
}
