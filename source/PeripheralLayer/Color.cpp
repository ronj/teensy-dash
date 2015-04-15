#include "Color.h"

#include <algorithm>

PeripheralLayer::Color::HSV PeripheralLayer::Color::Convert(const PeripheralLayer::Color::RGB& rgb)
{
	HSV hsv;

	uint8_t rgbMin = std::min(std::min(rgb.r, rgb.g), rgb.b);
	uint8_t rgbMax = std::max(std::max(rgb.r, rgb.g), rgb.b);

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

PeripheralLayer::Color::RGB PeripheralLayer::Color::Convert(const PeripheralLayer::Color::HSV& hsv)
{
	RGB rgb;
	unsigned char region, p, q, t;
	unsigned int h, s, v, remainder;

	if (hsv.s == 0)
	{
		rgb.r = hsv.v;
		rgb.g = hsv.v;
		rgb.b = hsv.v;
		return rgb;
	}

	// converting to 16 bit to prevent overflow
	h = hsv.h;
	s = hsv.s;
	v = hsv.v;

	region = h / 43;
	remainder = (h - (region * 43)) * 6;

	p = (v * (255 - s)) >> 8;
	q = (v * (255 - ((s * remainder) >> 8))) >> 8;
	t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

	switch (region)
	{
	case 0:
		rgb.r = v;
		rgb.g = t;
		rgb.b = p;
		break;
	case 1:
		rgb.r = q;
		rgb.g = v;
		rgb.b = p;
		break;
	case 2:
		rgb.r = p;
		rgb.g = v;
		rgb.b = t;
		break;
	case 3:
		rgb.r = p;
		rgb.g = q;
		rgb.b = v;
		break;
	case 4:
		rgb.r = t;
		rgb.g = p;
		rgb.b = v;
		break;
	default:
		rgb.r = v;
		rgb.g = p;
		rgb.b = q;
		break;
	}

	return rgb;
}
