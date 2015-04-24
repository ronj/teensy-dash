#pragma once

#include <cinttypes>

namespace HardwareLayer
{
	class DisplayDriver;
}

namespace PeripheralLayer
{
	class GraphicContext
	{
	public:
		GraphicContext(HardwareLayer::DisplayDriver& driver);

		void DrawPixel(int16_t x, int16_t y, uint32_t color);

		void DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color);
		void DrawVerticalLine(int16_t x, int16_t y, int16_t h, uint32_t color);
		void DrawHorizontalLine(int16_t x, int16_t y, int16_t w, uint32_t color);

		void DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color);
		void DrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t radius, uint32_t color);
		void DrawCircle(int16_t x, int16_t y, int16_t r, uint32_t color);
    	void DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t color);

		void FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color);
    	void FillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t radius, uint32_t color);
    	void FillCircle(int16_t x, int16_t y, int16_t r, uint32_t color);
    	void FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t color);
		void FillScreen(uint32_t color);

		void DrawBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int16_t w, int16_t h, uint32_t color);
		void DrawChar(int16_t x, int16_t y, unsigned char c, uint32_t fgcolor, uint32_t bgcolor, const uint8_t* font, uint8_t size);

		int16_t Width();
		int16_t Height();

		void Update();

	private:
		void DrawCircleHelper(int16_t x, int16_t y, int16_t r, uint8_t cornername, uint32_t color);
		void FillCircleHelper(int16_t x, int16_t y, int16_t r, uint8_t cornername, int16_t delta, uint32_t color);

	private:
		HardwareLayer::DisplayDriver& m_Display;
	};
}
