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

			RGB(uint32_t rgba)
				: r((rgba >> 24) & 0xFF)
				, g((rgba >> 16) & 0xFF)
				, b((rgba >> 8) & 0xFF)
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
		Color::RGB Interpolate(Color::RGB a, Color::RGB b, float t, InterpolationMethod interpolator)
		{
			// 0.0 <= t <= 1.0
			Color::HSV ca = a;
			Color::HSV cb = b;
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
