#include "yaffut.h"
#include "hippomocks.h"

#include "PeripheralLayer/Configuration.h"
#include "PeripheralLayer/PulseCounter.h"

#include "ApplicationLayer/Models/SpeedModel.h"

struct SpeedModelTest
{
	MockRepository mocks;
	PeripheralLayer::Configuration* configuration = mocks.Mock<PeripheralLayer::Configuration>();
	PeripheralLayer::PulseCounter* pulseCounter = mocks.Mock<PeripheralLayer::PulseCounter>();

	// Period at which speed pulses are evaluated.
	// In this case speed pulses are measured for the duration
	// of one second before a new calculation is made.
	static const unsigned long DEFAULT_SPEED_PERIOD = 1000;
};

TEST(SpeedModelTest, should_not_calculate_speed_when_period_is_not_yet_elapsed)
{
	mocks.ExpectCall(configuration, PeripheralLayer::Configuration::GetVSSPulsesPerKm).Return(1000);
	ApplicationLayer::Models::SpeedModel speed(*configuration, *pulseCounter);

	EXPECT_EQ(0, speed.GetRawValue());
	EXPECT_EQ("0", speed.GetFormattedValue());

	speed.Update(DEFAULT_SPEED_PERIOD - 1);

	EXPECT_EQ(0, speed.GetRawValue());
	EXPECT_EQ("0", speed.GetFormattedValue());
}

TEST(SpeedModelTest, should_calculate_common_speeds_from_vss_pulses)
{
	mocks.ExpectCall(configuration, PeripheralLayer::Configuration::GetVSSPulsesPerKm).Return(3600);
	ApplicationLayer::Models::SpeedModel speed(*configuration, *pulseCounter);

	unsigned long timestamp = 0;

	for (auto i : { 10, 20, 30, 50, 60, 70, 80, 90, 100, 120, 150, 220 })
	{
		mocks.ExpectCall(pulseCounter, PeripheralLayer::PulseCounter::GetCount).Return(i);
		speed.Update(timestamp += DEFAULT_SPEED_PERIOD);

		EXPECT_EQ(i * 10, speed.GetRawValue());
		EXPECT_EQ(std::to_string(i), speed.GetFormattedValue());
	}
}

TEST(SpeedModelTest, should_calculate_speed_for_period_longer_than_default)
{
	const float longerPeriod = 1250.f;

	mocks.ExpectCall(configuration, PeripheralLayer::Configuration::GetVSSPulsesPerKm).Return(3600);
	ApplicationLayer::Models::SpeedModel speed(*configuration, *pulseCounter);

	unsigned long timestamp = 0;

	for (auto i : { 15, 25, 35, 55, 65, 75, 85, 95, 105, 125, 155, 225 })
	{
		mocks.ExpectCall(pulseCounter, PeripheralLayer::PulseCounter::GetCount).Return(i);
		speed.Update(timestamp += static_cast<unsigned long>(longerPeriod));

		EXPECT_EQ((i * (DEFAULT_SPEED_PERIOD / longerPeriod)) * 10, speed.GetRawValue());
		EXPECT_EQ(std::to_string(static_cast<unsigned int>(i * (DEFAULT_SPEED_PERIOD / longerPeriod))), speed.GetFormattedValue());
	}
}
