#include "GraphicContext.h"

#include "Bitmap.h"
#include "Color.h"
#include "Font.h"

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
	const bool steep = NormalizeCoordinates(x0, y0, x1, y1);

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

uint32_t Brightness(uint32_t color, float brightness)
{
	PeripheralLayer::Color::RGB c(color >> 8);
	c.r = std::round((float)c.r * brightness);
	c.g = std::round((float)c.g * brightness);
	c.b = std::round((float)c.b * brightness);

	return c.ToRGBA(0xff);
}

void PeripheralLayer::GraphicContext::DrawWuLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color)
{
	const bool steep = NormalizeCoordinates(x0, y0, x1, y1);

	int dx = x1 - x0;
	int dy = y1 - y0;
	
	if (dy == 0)
	{
		//DrawHorizontalLine(x0, y0, )
	}

	if (dx == 0)
	{
		//DrawVerticalLine();
	}
	
	float gradient = (float)dy / (float)dx;

	// handle first endpoint
	int xend = std::round(x0);
	float yend = y0 + gradient * (xend - x0);
	float xgap = rfpart(x0 + 0.5);
	int xpxl1 = xend;  //this will be used in the main loop
	int ypxl1 = ipart(yend);

	if (steep)
	{
		DrawPixel(xpxl1, ypxl1, Brightness(color, rfpart(yend) * xgap));
		DrawPixel(xpxl1, ypxl1 + 1, Brightness(color, fpart(yend) * xgap));
	}
	else
	{
		DrawPixel(ypxl1, xpxl1, Brightness(color, rfpart(yend) * xgap));
		DrawPixel(ypxl1 + 1, xpxl1, Brightness(color, fpart(yend) * xgap));
	}
	float intery = yend + gradient; // first y-intersection for the main loop

	// handle second endpoint
	xend = std::round(x1);
	yend = y1 + gradient * (xend - x1);
	xgap = fpart(x1 + 0.5);
	int xpxl2 = xend; //this will be used in the main loop
	int ypxl2 = ipart(yend);
	if (steep)
	{
		DrawPixel(xpxl2, ypxl2, Brightness(color, rfpart(yend) * xgap));
		DrawPixel(xpxl2, ypxl2 + 1, Brightness(color, fpart(yend) * xgap));
	}
	else
	{
		DrawPixel(ypxl2, xpxl2, Brightness(color, rfpart(yend) * xgap));
		DrawPixel(ypxl2 + 1, xpxl2 + 1, Brightness(color, fpart(yend) * xgap));
	}

	// main loop
	for (int x = xpxl1 + 1; x <= xpxl2 - 1; x++)
	{
		if (steep)
		{
			DrawPixel(x, ipart(intery), Brightness(color, rfpart(intery)));
			DrawPixel(x, ipart(intery) + 1, Brightness(color, fpart(intery)));
		}
		else
		{
			DrawPixel(ipart(intery), x, Brightness(color, rfpart(intery)));
			DrawPixel(ipart(intery) + 1, x, Brightness(color, fpart(intery)));
		}
		intery = intery + gradient;
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
    unsigned int x = r, y = 0; //local coords     
    int          cd2 = 0;      //current distance squared - radius squared

    if (r == 0) return;

    DrawPixel(xc - r, yc, color);
    DrawPixel(xc + r, yc, color);
    DrawPixel(xc, yc - r, color);
    DrawPixel(xc, yc + r, color);

    while (x > y)    //only formulate 1/8 of circle
    {
        cd2 -= (--x) - (++y);
        if (cd2 < 0) cd2 += x++;

        DrawPixel(xc - x, yc - y, color); //upper left left
        DrawPixel(xc - y, yc - x, color); //upper upper left
        DrawPixel(xc + y, yc - x, color); //upper upper right
        DrawPixel(xc + x, yc - y, color); //upper right right
        DrawPixel(xc - x, yc + y, color); //lower left left
        DrawPixel(xc - y, yc + x, color); //lower lower left
        DrawPixel(xc + y, yc + x, color); //lower lower right
        DrawPixel(xc + x, yc + y, color); //lower right right
     }
}

void PeripheralLayer::GraphicContext::DrawWuCircle(int16_t xc, int16_t yc, int16_t r, uint32_t color)
{
	int x = 0;
	double yprev = r;
	int y1 = r;
	double ynew = r;
	double fparttmp = 0;
	double fpartptmp = 0;
	int ynewint = 0;
	int yprevint = 0;

	DrawPixel(xc - r, yc, color);
	DrawPixel(xc + r, yc, color);
	DrawPixel(xc, yc - r, color);
	DrawPixel(xc, yc + r, color);

	while (x < y1)
	{
		x++;
		ynew = std::sqrt(r*r - x*x);
		y1 = (int)std::ceil(ynew);

		if (yprev - ipart(ynew) > 1)
		{
			ynewint = (int)std::ceil(ynew);
			yprevint = (int)std::ceil(yprev);
			fparttmp = (fpart(ynew) == 0) ? 1 : fpart(ynew);
			fpartptmp = (fpart(yprev) == 0) ? 0.01 : fpart(yprev);

			WuCircleHelper(xc, yc, x, ynewint, color, fparttmp);
			WuCircleHelper(xc, yc, x, yprevint, color, fpartptmp);
		}
		else{
			fparttmp = (fpart(ynew) == 0) ? 1 : fpart(ynew);
			WuCircleHelper(xc, yc, x, y1, color, fparttmp);
		}

		yprev = ynew;
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

void PeripheralLayer::GraphicContext::DrawBitmap(int16_t x, int16_t y, const Bitmaps::Bitmap& bitmap, uint32_t color)
{
	const int16_t byteWidth = (bitmap.width + 7) / 8;

	for (int16_t j = 0; j < bitmap.height; ++j)
	{
		for (int16_t i = 0; i < bitmap.width; ++i)
		{
			if (pgm_read_byte(bitmap.data + j * byteWidth + i / 8) & (128 >> (i & 7)))
			{
				DrawPixel(x + i, y + j, color);
			}
		}
	}
}

void PeripheralLayer::GraphicContext::DrawChar(int16_t x, int16_t y, unsigned char c, uint32_t fgcolor, uint32_t bgcolor, const Fonts::Font& font, uint8_t size)
{
	if ((x >= m_Display.Width()) ||   // Clip right
		(y >= m_Display.Height()) ||  // Clip bottom
		((x + font.descriptor[c].width * size - 1) < 0) ||   // Clip left
		((y + font.descriptor[c].height * size - 1) < 0))    // Clip top
	{
		return;
	}

	uint16_t fontIndex = font.descriptor[c].offset;
	uint8_t bitCount = 0;

	for (int8_t i = 0; i < font.descriptor[c].height; ++i)
	{
		uint8_t line = 0;

		for (int8_t j = 0; j < font.descriptor[c].width; ++j)
		{
			if (bitCount++ % 8 == 0)
			{
				line = pgm_read_byte(font.data + fontIndex++);
			}

			if (line & 0x80)
			{
				(size == 1) ? DrawPixel(x + j, y + i, fgcolor) :
					FillRect(x + (j * size), y + (i * size), size, size, fgcolor);
			}
			else if (bgcolor != fgcolor)
			{
				(size == 1) ? DrawPixel(x + j, y + i, bgcolor) :
					FillRect(x + (j * size), y + (i * size), size, size, bgcolor);
			}

			line <<= 1;
		}

		bitCount = 0;
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

	while (x < y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		if (cornername & 0x1)
		{
			DrawVerticalLine(x0 + x, y0 - y, 2 * y + 1 + delta, color);
			DrawVerticalLine(x0 + y, y0 - x, 2 * x + 1 + delta, color);
		}
		if (cornername & 0x2)
		{
			DrawVerticalLine(x0 - x, y0 - y, 2 * y + 1 + delta, color);
			DrawVerticalLine(x0 - y, y0 - x, 2 * x + 1 + delta, color);
		}
	}
}

bool PeripheralLayer::GraphicContext::NormalizeCoordinates(int16_t& x0, int16_t& y0, int16_t& x1, int16_t& y1)
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

	return steep;
}

void PeripheralLayer::GraphicContext::WuCircleHelper(int xc, int yc, int x, int y, uint32_t color, float alpha)
{
	DrawPixel(xc + x, (yc + y), Brightness(color, alpha));
	DrawPixel(xc - x, (yc + y), Brightness(color, alpha));
	DrawPixel(xc + x, (yc - y), Brightness(color, alpha));
	DrawPixel(xc - x, (yc - y), Brightness(color, alpha));
	DrawPixel(xc + y, (yc + x), Brightness(color, alpha));
	DrawPixel(xc - y, (yc + x), Brightness(color, alpha));
	DrawPixel(xc + y, (yc - x), Brightness(color, alpha));
	DrawPixel(xc - y, (yc - x), Brightness(color, alpha));
}
