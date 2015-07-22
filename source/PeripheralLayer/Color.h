#pragma once

#include <cinttypes>

namespace PeripheralLayer
{
	namespace Color
	{
		struct RGB;
		struct HSV;
		struct HSL;

		HSV ConvertHSV(const RGB& rgb);
		RGB Convert(const HSV& hsv);

		HSL ConvertHSL(const RGB& rgb);
		RGB Convert(const HSL& hsl);

		struct RGB
		{
			typedef uint8_t rgb_data_t;

			RGB() : RGB(0, 0, 0) {}

			explicit RGB(uint32_t rgb)
				: r((rgb >> 16) & 0xFF)
				, g((rgb >>  8) & 0xFF)
				, b((rgb >>  0) & 0xFF)
			{
			}

			RGB(rgb_data_t r, rgb_data_t g, rgb_data_t b)
				: r(r)
				, g(g)
				, b(b)
			{
			}

			RGB(const HSV& hsv)
			{
				*this = Convert(hsv);
			}

			RGB(const HSL& hsl)
			{
				*this = Convert(hsl);
			}

			uint32_t ToRGBA(rgb_data_t a) const
			{
				return (r << 24) + (g << 16) + (b << 8) + a;
			}

			uint32_t ToRGB() const
			{
				return (r << 16) + (g << 8) + b;
			}

			union
			{
				struct
				{
					union
					{
						rgb_data_t r;
						rgb_data_t red;
					};
					union
					{
						rgb_data_t g;
						rgb_data_t green;
					};
					union
					{
						rgb_data_t b;
						rgb_data_t blue;
					};
				};

				rgb_data_t raw[3];
			};
		};

		struct HSV
		{
			typedef uint8_t hsv_data_t;

			HSV() : HSV(0, 0, 0) {}

			HSV(hsv_data_t h, hsv_data_t s, hsv_data_t v)
				: h(h)
				, s(s)
				, v(v)
			{
			}

			HSV(const RGB& rgb)
			{
				*this = ConvertHSV(rgb);
			}

			union
			{
				struct
				{
					union
					{
						hsv_data_t h;
						hsv_data_t hue;
					};
					union
					{
						hsv_data_t s;
						hsv_data_t saturation;
					};
					union
					{
						hsv_data_t v;
						hsv_data_t value;
					};
				};

				hsv_data_t raw[3];
			};
		};

		struct HSL
		{
			typedef float hsl_data_t;

			HSL() : HSL(0, 0, 0) {}

			HSL(hsl_data_t h, hsl_data_t s, hsl_data_t l)
				: h(h)
				, s(s)
				, l(l)
			{
			}

			HSL(const RGB& rgb)
			{
				*this = ConvertHSL(rgb);
			}

			union
			{
				struct
				{
					union
					{
						hsl_data_t h;
						hsl_data_t hue;
					};
					union
					{
						hsl_data_t s;
						hsl_data_t saturation;
					};
					union
					{
						hsl_data_t l;
						hsl_data_t luminance;
					};
				};

				hsl_data_t raw[3];
			};
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

		Color::RGB Darken(const Color::RGB& color, float amount);

		//Color::RGB Desaturate(Color::RGB c, int amount);
	}
}
