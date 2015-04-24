#pragma once

#include <cinttypes>

namespace PeripheralLayer
{
	namespace Color
	{
		struct RGB;
		struct HSV;

		HSV Convert(const RGB& rgb);
		RGB Convert(const HSV& hsv);

		struct RGB
		{
			RGB() : RGB(0, 0, 0) {}

			explicit RGB(uint32_t rgb)
				: r((rgb >> 16) & 0xFF)
				, g((rgb >> 8) & 0xFF)
				, b(rgb & 0xFF)
			{
			}

			RGB(uint8_t r, uint8_t g, uint8_t b)
				: r(r)
				, g(g)
				, b(b)
			{
			}

			RGB(const HSV& hsv)
			{
				*this = Convert(hsv);
			}

			uint32_t ToRGBA(uint8_t a) const
			{
				return (r << 24) + (g << 16) + (b << 8) + a;
			}

			uint32_t ToRGB() const
			{
				return (r << 16) + (g << 8) + b;
			}

			uint8_t r;
			uint8_t g;
			uint8_t b;
		};

		struct HSV
		{
			HSV() : HSV(0, 0, 0) {}

			HSV(uint8_t h, uint8_t s, uint8_t v)
				: h(h)
				, s(s)
				, v(v)
			{
			}

			HSV(const RGB& rgb)
			{
				*this = Convert(rgb);
			}

			uint8_t h;
			uint8_t s;
			uint8_t v;
		};

		template <typename InterpolationMethod>
		Color::RGB Interpolate(const Color::RGB& start, const Color::RGB& end, float t, InterpolationMethod interpolator)
		{
			// 0.0 <= t <= 1.0
			Color::HSV ca = start;
			Color::HSV cb = end;
			Color::HSV final;

			final.h = interpolator(ca.h, cb.h, t);
			final.s = interpolator(ca.s, cb.s, t);
			final.v = interpolator(ca.v, cb.v, t);

			return final;
		}

		//Color::RGB Desaturate(Color::RGB c, int amount)
		//{

		//}
	}
}
