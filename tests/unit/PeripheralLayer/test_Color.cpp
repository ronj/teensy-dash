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

	void hsv_rgb_hsv_conversion_helper(uint8_t h, uint8_t s, uint8_t v)
	{
		Color::HSV expected(h, s, v);
		Color::RGB rgb = expected;
		Color::HSV actual = rgb;

		EXPECT_EQ(expected.h, actual.h);
		EXPECT_EQ(expected.s, actual.s);
		EXPECT_EQ(expected.v, actual.v);
	}
};

TEST(ColorTest, test_should_construct_rgb_color)
{
	check_rgb(0, 0, 0, Color::RGB());
	check_rgb(0xFF, 0xAA, 0x00, Color::RGB(0xFF, 0xAA, 0x00));
	check_rgb(0x12, 0x34, 0x56, Color::RGB(0x123456));
}

TEST(ColorTest, test_should_construct_hsv_color)
{
	check_hsv(0, 0, 0, Color::HSV());
	check_hsv(30, 100, 100, Color::HSV(30, 100, 100));
}

TEST(ColorTest, test_should_convert_colorspaces)
{
	hsv_rgb_hsv_conversion_helper(20, 255, 100);
	hsv_rgb_hsv_conversion_helper(0, 0, 150);
	//hsv_rgb_hsv_conversion_helper(11, 22, 33);
}
