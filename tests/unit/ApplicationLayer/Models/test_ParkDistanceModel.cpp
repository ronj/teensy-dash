#include "yaffut.h"
#include "hippomocks.h"

#include "PeripheralLayer/ParkDistanceDecoder.h"

#include "ApplicationLayer/Models/ParkDistanceModel.h"

struct ParkDistanceModelTest
{
	MockRepository mocks;
	PeripheralLayer::ParkDistanceDecoder* parkDistanceDecoder = mocks.Mock<PeripheralLayer::ParkDistanceDecoder>();
};

uint32_t PackDistances(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
	return (a << 24) | (b << 16) | (c << 8) | d;
}

TEST(ParkDistanceModelTest, should_have_correct_initial_value)
{
	ApplicationLayer::Models::ParkDistanceModel pdc(*parkDistanceDecoder);

	EXPECT_EQ(std::numeric_limits<uint32_t>::max(), pdc.GetRawValue());
	EXPECT_EQ("-.--", pdc.GetFormattedValue());
}

TEST(ParkDistanceModelTest, should_display_distance_to_closest_object)
{
	ApplicationLayer::Models::ParkDistanceModel pdc(*parkDistanceDecoder);

	uint32_t packed = PackDistances(10, 20, 30, 40);
	mocks.ExpectCall(parkDistanceDecoder, PeripheralLayer::ParkDistanceDecoder::GetPackedDistances).Return(packed);

	pdc.Update(0);

	EXPECT_EQ(packed, pdc.GetRawValue());
	EXPECT_EQ("0.10", pdc.GetFormattedValue());
}

TEST(ParkDistanceModelTest, should_ignore_invalid_measurements)
{
	ApplicationLayer::Models::ParkDistanceModel pdc(*parkDistanceDecoder);

	uint32_t packed = PackDistances(255, 255, 254, 255);
	mocks.ExpectCall(parkDistanceDecoder, PeripheralLayer::ParkDistanceDecoder::GetPackedDistances).Return(packed);

	pdc.Update(0);

	EXPECT_EQ(packed, pdc.GetRawValue());
	EXPECT_EQ("2.54", pdc.GetFormattedValue());
}

TEST(ParkDistanceModelTest, should_show_no_value_when_all_measurements_are_invalid)
{
	ApplicationLayer::Models::ParkDistanceModel pdc(*parkDistanceDecoder);

	uint32_t packed = PackDistances(255, 255, 255, 255);
	mocks.ExpectCall(parkDistanceDecoder, PeripheralLayer::ParkDistanceDecoder::GetPackedDistances).Return(packed);

	pdc.Update(0);

	EXPECT_EQ(packed, pdc.GetRawValue());
	EXPECT_EQ("-.--", pdc.GetFormattedValue());
}
