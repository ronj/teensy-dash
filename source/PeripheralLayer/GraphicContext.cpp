#include "GraphicContext.h"

#include "HardwareLayer/DisplayDriver.h"

#include <algorithm>
#include <cstdlib>

#ifdef __AVR__
	#include <avr/pgmspace.h>
#else
	#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif

PeripheralLayer::GraphicContext::GraphicContext(HardwareLayer::DisplayDriver& driver)
	: m_Display(driver)
{
}

void PeripheralLayer::GraphicContext::DrawPixel(int16_t x, int16_t y, uint32_t color)
{
	m_Display.DrawPixel(x, y, color);
}

void PeripheralLayer::GraphicContext::DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color)
{
	const bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
	if (steep)
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
	}

	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	const int16_t dx = x1 - x0;
	const int16_t dy = std::abs(y1 - y0);
	int16_t error = dx / 2;
	int16_t ystep = (y0 < y1) ? 1 : -1;

	for (; x0 <= x1; x0++)
	{
		steep ? DrawPixel(y0, x0, color) :
				DrawPixel(x0, y0, color);

		error -= dy;
		if (error < 0)
		{
			y0 += ystep;
			error += dx;
		}
	}
}

void PeripheralLayer::GraphicContext::DrawVerticalLine(int16_t x, int16_t y, int16_t h, uint32_t color)
{
	if (!m_Display.DrawVerticalLine(x, y, h, color))
	{
		DrawLine(x, y, x, y + h - 1, color);
	}
}

void PeripheralLayer::GraphicContext::DrawHorizontalLine(int16_t x, int16_t y, int16_t w, uint32_t color)
{
	if (!m_Display.DrawHorizontalLine(x, y, w, color))
	{
		DrawLine(x, y, x + w - 1, y, color);
	}
}

void PeripheralLayer::GraphicContext::DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)
{
	DrawHorizontalLine(x, y, w, color);
	DrawHorizontalLine(x, y + h - 1, w, color);
	DrawVerticalLine(x, y, h, color);
	DrawVerticalLine(x + w - 1, y, h, color);
}

void PeripheralLayer::GraphicContext::DrawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint32_t color)
{

}

void PeripheralLayer::GraphicContext::DrawCircle(int16_t xc, int16_t yc, int16_t r, uint32_t color)
{
	// http://www.willperone.net/Code/codecircle.php
	// http://rosettacode.org/wiki/Bitmap/Midpoint_circle_algorithm#C
	
	/*
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t dx = 0;
	int16_t dy = r;

	DrawPixel(x    , y + r, color);
	DrawPixel(x    , y - r, color);
	DrawPixel(x + r, y    , color);
	DrawPixel(x - r, y    , color);

	while (dx < dy) {
		if (f >= 0)
		{
			dy--;
			ddF_y += 2;
			f += ddF_y;
		}

		dx++;
		ddF_x += 2;
		f += ddF_x;

		DrawPixel(x + dx, y + dy, color);
		DrawPixel(x - dx, y + dy, color);
		DrawPixel(x + dx, y - dy, color);
		DrawPixel(x - dx, y - dy, color);
		DrawPixel(x + dy, y + dx, color);
		DrawPixel(x - dy, y + dx, color);
		DrawPixel(x + dy, y - dx, color);
		DrawPixel(x - dy, y - dx, color);
	}
	*/

/*
    int x = 0; 
    int y = r; 
    int p = 3 - 2 * r;
    if (!r) return;     
    while (y >= x) // only formulate 1/8 of circle
    {
        DrawPixel(xc-x, yc-y, color);//upper left left
        DrawPixel(xc-y, yc-x, color);//upper upper left
        DrawPixel(xc+y, yc-x, color);//upper upper right
        DrawPixel(xc+x, yc-y, color);//upper right right
        DrawPixel(xc-x, yc+y, color);//lower left left
        DrawPixel(xc-y, yc+x, color);//lower lower left
        DrawPixel(xc+y, yc+x, color);//lower lower right
        DrawPixel(xc+x, yc+y, color);//lower right right
        if (p < 0) p += 4*x++ + 6; 
              else p += 4*(x++ - y--) + 10; 
     }
*/

    unsigned int x = r, y= 0; //local coords     
    int          cd2= 0;      //current distance squared - radius squared

    if (!r) return; 
    DrawPixel(xc - r, yc, color);
    DrawPixel(xc + r, yc, color);
    DrawPixel(xc, yc - r, color);
    DrawPixel(xc, yc + r, color);

    while (x > y)    //only formulate 1/8 of circle
    {
        cd2 -= (--x) - (++y);
        if (cd2 < 0) cd2 += x++;

        DrawPixel(xc-x, yc-y, color); //upper left left
        DrawPixel(xc-y, yc-x, color); //upper upper left
        DrawPixel(xc+y, yc-x, color); //upper upper right
        DrawPixel(xc+x, yc-y, color); //upper right right
        DrawPixel(xc-x, yc+y, color); //lower left left
        DrawPixel(xc-y, yc+x, color); //lower lower left
        DrawPixel(xc+y, yc+x, color); //lower lower right
        DrawPixel(xc+x, yc+y, color); //lower right right
     }
}

void PeripheralLayer::GraphicContext::DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t color)
{
	DrawLine(x0, y0, x1, y1, color);
	DrawLine(x1, y1, x2, y2, color);
	DrawLine(x2, y2, x0, y0, color);
}

void PeripheralLayer::GraphicContext::FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)
{
	if (!m_Display.FillRect(x, y, w, h, color))
	{
		for (int16_t i = x; i < x + w; ++i)
		{
			DrawVerticalLine(i, y, h, color);
		}
	}
}

void PeripheralLayer::GraphicContext::FillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint32_t color)
{

}

void PeripheralLayer::GraphicContext::FillCircle(int16_t x, int16_t y, int16_t r, uint32_t color)
{
	DrawVerticalLine(x, y - r, 2 * r + 1, color);
	FillCircleHelper(x, y, r, 3, 0, color);
}

void PeripheralLayer::GraphicContext::FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t color)
{

}

void PeripheralLayer::GraphicContext::FillScreen(uint32_t color)
{
	FillRect(0, 0, m_Display.Width(), m_Display.Height(), color);
}

void PeripheralLayer::GraphicContext::DrawBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int16_t w, int16_t h, uint32_t color)
{
	const int16_t byteWidth = (w + 7) / 8;

	for (int16_t j = 0; j < h; ++j)
	{
		for (int16_t i = 0; i < w; ++i)
		{
			if (pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7)))
			{
				DrawPixel(x + i, y + j, color);
			}
		}
	}
}

void PeripheralLayer::GraphicContext::DrawChar(int16_t x, int16_t y, unsigned char c, uint32_t fgcolor, uint32_t bgcolor, const uint8_t* font, uint8_t size)
{
	if ((x >= m_Display.Width()) ||   // Clip right
		(y >= m_Display.Height()) ||  // Clip bottom
		((x + 6 * size - 1) < 0) ||   // Clip left
		((y + 8 * size - 1) < 0))     // Clip top
	{
		return;
	}

	for (int8_t i = 0; i < 6; ++i)
	{
		uint8_t line = (i == 5) ? 0x00 : pgm_read_byte(font + (c * 5) + i);

		for (int8_t j = 0; j < 8; ++j)
		{
			if (line & 0x1)
			{
				(size == 1) ? DrawPixel(x + i, y + j, fgcolor) :
					FillRect(x + (i * size), y + (j * size), size, size, fgcolor);
			}
			else if (bgcolor != fgcolor)
			{
				(size == 1) ? DrawPixel(x + i, y + j, bgcolor) :
					FillRect(x + i*size, y + j*size, size, size, bgcolor);
			}

			line >>= 1;
		}
	}
}

void PeripheralLayer::GraphicContext::Update()
{
	m_Display.Update();
}

void PeripheralLayer::GraphicContext::DrawCircleHelper(int16_t x, int16_t y, int16_t r, uint8_t cornername, uint32_t color)
{

}

void PeripheralLayer::GraphicContext::FillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint32_t color)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		if (cornername & 0x1) {
			DrawVerticalLine(x0 + x, y0 - y, 2 * y + 1 + delta, color);
			DrawVerticalLine(x0 + y, y0 - x, 2 * x + 1 + delta, color);
		}
		if (cornername & 0x2) {
			DrawVerticalLine(x0 - x, y0 - y, 2 * y + 1 + delta, color);
			DrawVerticalLine(x0 - y, y0 - x, 2 * x + 1 + delta, color);
		}
	}
}

int16_t PeripheralLayer::GraphicContext::Width()
{
	return m_Display.Width();
}

int16_t PeripheralLayer::GraphicContext::Height()
{
	return m_Display.Height();
}
