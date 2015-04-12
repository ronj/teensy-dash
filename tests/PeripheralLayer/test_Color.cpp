#include "yaffut.h"

#include "PeripheralLayer/Color.h"

using namespace PeripheralLayer;

struct ColorTest {};

TEST(ColorTest, test_should_construct_rgb_color)
{
	Color::RGB rgb(0xFF, 0xAA, 0x00);

	EXPECT_EQ(0xFF, rgb.r);
	EXPECT_EQ(0xAA, rgb.g);
	EXPECT_EQ(0x00, rgb.b);
}

TEST(ColorTest, test_should_construct_hsv_color)
{
	Color::HSV hsv(30, 100, 100);

	EXPECT_EQ(30, hsv.h);
	EXPECT_EQ(100, hsv.s);
	EXPECT_EQ(100, hsv.v);
}

TEST(ColorTest, test_should_convert_hsv_to_rgb)
{
	Color::HSV hsv(30, 255, 100);

	Color::RGB rgb = hsv;
	Color::HSV actual = rgb;

	EXPECT_EQ(30, actual.h);
	EXPECT_EQ(255, actual.s);
	EXPECT_EQ(100, actual.v);
}
