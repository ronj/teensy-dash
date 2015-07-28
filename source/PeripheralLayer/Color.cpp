#include "Color.h"

#include <algorithm>

namespace {
	float hue2rgb(float p, float q, float t)
	{
		if (t < 0) t += 1;
		if (t > 1) t -= 1;
		if (t < 1.f / 6) return p + (q - p) * 6 * t;
		if (t < 1.f / 2) return q;
		if (t < 2.f / 3) return p + (q - p) * (2 / 3 - t) * 6;
		return p;
	}
}

PeripheralLayer::Color::HSV PeripheralLayer::Color::ConvertHSV(const Color::RGB& rgb)
{
	HSV hsv;

	uint8_t rgbMin = std::min({ rgb.r, rgb.g, rgb.b });
	uint8_t rgbMax = std::max({ rgb.r, rgb.g, rgb.b });

	hsv.v = rgbMax;
	if (hsv.v == 0)
	{
		hsv.h = 0;
		hsv.s = 0;
		return hsv;
	}

	hsv.s = 255 * ((long)(rgbMax - rgbMin)) / hsv.v;
	if (hsv.s == 0)
	{
		hsv.h = 0;
		return hsv;
	}

	if (rgbMax == rgb.r)
		hsv.h = 0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
	else if (rgbMax == rgb.g)
		hsv.h = 85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
	else
		hsv.h = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);

	return hsv;
}

PeripheralLayer::Color::RGB PeripheralLayer::Color::Convert(const Color::HSV& hsv)
{
	if (hsv.s == 0)
	{
		return { hsv.v, hsv.v, hsv.v };
	}

	// converting to 16 bit to prevent overflow
	uint16_t h = hsv.h;
	uint16_t s = hsv.s;
	uint16_t v = hsv.v;

	uint8_t region = h / 43;
	uint16_t remainder = (h - (region * 43)) * 6;

	uint8_t p = (v * (255 - s)) >> 8;
	uint8_t q = (v * (255 - ((s * remainder) >> 8))) >> 8;
	uint8_t t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

	switch (region)
	{
		case 0: return { static_cast<uint8_t>(v), t, p };
		case 1: return { q, static_cast<uint8_t>(v), p };
		case 2: return { p, static_cast<uint8_t>(v), t };
		case 3: return { p, q, static_cast<uint8_t>(v) };
		case 4: return { t, p, static_cast<uint8_t>(v) };
	}

	return { static_cast<uint8_t>(v), p, q };
}

PeripheralLayer::Color::HSL PeripheralLayer::Color::ConvertHSL(const Color::RGB& rgb)
{
	float rd = (float)rgb.r / 255;
	float gd = (float)rgb.g / 255;
	float bd = (float)rgb.b / 255;
	float max = std::max({ rd, gd, bd });
	float min = std::min({ rd, gd, bd });
	float h, s, l = (max + min) / 2;

	if (max == min) {
		h = s = 0; // achromatic
	}
	else {
		float d = max - min;
		s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
		if (max == rd) {
			h = (gd - bd) / d + (gd < bd ? 6 : 0);
		}
		else if (max == gd) {
			h = (bd - rd) / d + 2;
		}
		else if (max == bd) {
			h = (rd - gd) / d + 4;
		}
		h /= 6;
	}

	return HSL(h, s, l);
}

PeripheralLayer::Color::RGB PeripheralLayer::Color::Convert(const Color::HSL& hsl)
{
	float r, g, b;

	if (hsl.s == 0) {
		r = g = b = hsl.l; // achromatic
	}
	else {
		float q = hsl.l < 0.5 ? hsl.l * (1 + hsl.s) : hsl.l + hsl.s - hsl.l * hsl.s;
		float p = 2 * hsl.l - q;
		r = hue2rgb(p, q, hsl.h + 1 / 3);
		g = hue2rgb(p, q, hsl.h);
		b = hue2rgb(p, q, hsl.h - 1 / 3);
	}

	return { static_cast<uint8_t>(r * 255), static_cast<uint8_t>(g * 255), static_cast<uint8_t>(b * 255) };
}

PeripheralLayer::Color::RGB PeripheralLayer::Color::Darken(const Color::RGB& color, float amount)
{
	//ASSERT_THAT(amount > 0.f && amount < 1.f);
	Color::HSL hslColor = color;
	hslColor.l *= amount;
	return hslColor;
}
