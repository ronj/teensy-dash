#pragma once

#include <cinttypes>
#include <cmath>

#ifndef BUILD_FOR_EMULATOR
namespace std
{
	template <typename T>
	T round(T x)
	{
    	return (x > 0.0) ? std::floor(x + 0.5) : std::ceil(x - 0.5);
	}
}
#endif

namespace HardwareLayer
{
	class DisplayDriver;
}

namespace PeripheralLayer
{
	namespace Bitmaps
	{
		struct Bitmap;
	}

	namespace Fonts
	{
		struct Font;
	}

	struct Point
	{
		int16_t x;
		int16_t y;
	};

	class GraphicContext
	{
	public:
		GraphicContext(HardwareLayer::DisplayDriver& driver);

		void DrawPixel(int16_t x, int16_t y, uint32_t color);

		void DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color);
		void DrawVerticalLine(int16_t x, int16_t y, int16_t h, uint32_t color);
		void DrawHorizontalLine(int16_t x, int16_t y, int16_t w, uint32_t color);
		void DrawWuLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color);

		void DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color);
		void DrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t radius, uint32_t color);
		void DrawCircle(int16_t x, int16_t y, int16_t r, uint32_t color);
		void DrawWuCircle(int16_t xc, int16_t yc, int16_t r, uint32_t color);
    	void DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t color);
		void DrawPolygon(Point points[], uint16_t count, uint32_t color);

		void FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color);
    	void FillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t radius, uint32_t color);
    	void FillCircle(int16_t x, int16_t y, int16_t r, uint32_t color);
    	void FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t color);
		void FillScreen(uint32_t color);

		void DrawBitmap(int16_t x, int16_t y, const Bitmaps::Bitmap& bitmap, uint32_t color);

		void DrawChar(int16_t x, int16_t y, unsigned char c, uint32_t fgcolor, uint32_t bgcolor, const Fonts::Font& font, uint8_t size);

		int16_t Width() const;
		int16_t Height() const;

		void Update();

	private:
		void DrawCircleHelper(int16_t x, int16_t y, int16_t r, uint8_t cornername, uint32_t color);
		void FillCircleHelper(int16_t x, int16_t y, int16_t r, uint8_t cornername, int16_t delta, uint32_t color);

		bool NormalizeCoordinates(int16_t& x0, int16_t& y0, int16_t& x1, int16_t& y1);

		void WuCircleHelper(int xc, int yc, int x, int y, uint32_t color, float alpha);

		template <typename T>
		int ipart(T x)
		{
			return  static_cast<int>(std::floor(x));
		}

		template <typename T>
		int round(T x)
		{
			return ipart(x + static_cast<T>(.5));
		}

		template <typename T>
		T fpart(T x)
		{
			return std::round((x - std::floor(x)) * 100) / static_cast<T>(100);
		}

		template <typename T>
		T rfpart(T x)
		{
			return 1 - fpart(x);
		}

	private:
		HardwareLayer::DisplayDriver& m_Display;
	};
}
