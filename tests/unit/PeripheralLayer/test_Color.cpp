#include "yaffut.h"

#include "PeripheralLayer/Color.h"

using namespace PeripheralLayer;

struct ColorTest
{
	void check_rgb(uint8_t r, uint8_t g, uint8_t b, const Color::RGB& rgb)
	{
		EXPECT_EQ(r, rgb.r);
		EXPECT_EQ(g, rgb.g);
		EXPECT_EQ(b, rgb.b);
	}

	void check_hsv(uint8_t h, uint8_t s, uint8_t v, const Color::HSV& hsv)
	{
		EXPECT_EQ(h, hsv.h);
		EXPECT_EQ(s, hsv.s);
		EXPECT_EQ(v, hsv.v);
	}

	void check_hsl(uint8_t h, uint8_t s, uint8_t l, const Color::HSL& hsl)
	{
		EXPECT_EQ(h, hsl.h);
		EXPECT_EQ(s, hsl.s);
		EXPECT_EQ(l, hsl.l);
	}

	void hsv_rgb_hsv_conversion_helper(uint8_t h, uint8_t s, uint8_t v)
	{
		Color::HSV expected(h, s, v);
		Color::RGB rgb = expected;
		Color::HSV actual = rgb;

		EXPECT_EQ(expected.h, actual.h);
		EXPECT_EQ(expected.s, actual.s);
		EXPECT_EQ(expected.v, actual.v);
	}

	void hsl_rgb_hsl_conversion_helper(uint8_t h, uint8_t s, uint8_t l)
	{
		Color::HSL expected(h, s, l);
		Color::RGB rgb = expected;
		Color::HSL actual = rgb;

		EXPECT_EQ(expected.h, actual.h);
		EXPECT_EQ(expected.s, actual.s);
		EXPECT_EQ(expected.l, actual.l);
	}
};

TEST(ColorTest, should_construct_rgb_color)
{
	check_rgb(0, 0, 0, Color::RGB());
	check_rgb(0xFF, 0xAA, 0x00, Color::RGB(0xFF, 0xAA, 0x00));
	check_rgb(0x12, 0x34, 0x56, Color::RGB(0x123456));
}

TEST(ColorTest, should_construct_hsv_color)
{
	check_hsv(0, 0, 0, Color::HSV());
	check_hsv(30, 100, 100, Color::HSV(30, 100, 100));
}

TEST(ColorTest, should_construct_hsl_color)
{
	check_hsl(0, 0, 0, Color::HSL());
	check_hsl(80, 90, 60, Color::HSL(80, 90, 60));
}

TEST(ColorTest, should_convert_rgb_hsv_colorspaces)
{
	hsv_rgb_hsv_conversion_helper(0, 0, 0);
	hsv_rgb_hsv_conversion_helper(20, 255, 100);
	hsv_rgb_hsv_conversion_helper(0, 0, 255);
	//hsv_rgb_hsv_conversion_helper(0, 255, 0);
	//hsv_rgb_hsv_conversion_helper(255, 0, 255);
	//hsv_rgb_hsv_conversion_helper(11, 22, 33);

	//hsl_rgb_hsl_conversion_helper(10, 20, 30);
}
