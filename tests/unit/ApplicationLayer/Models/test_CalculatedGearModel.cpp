#include "yaffut.h"
#include "hippomocks.h"

#include "PeripheralLayer/Configuration.h"

#include "ApplicationLayer/Models/Model.h"
#include "ApplicationLayer/Models/CalculatedGearModel.h"

#include <list>

struct CalculatedGearModelTest
{
	MockRepository mocks;
	PeripheralLayer::Configuration* configuration = mocks.Mock<PeripheralLayer::Configuration>();
	ApplicationLayer::Models::Model* speed = mocks.Mock<ApplicationLayer::Models::Model>();
	ApplicationLayer::Models::Model* rpm = mocks.Mock<ApplicationLayer::Models::Model>();

	CalculatedGearModelTest()
	{
		/* Configuration of my car, Peugeot 306 1.6 8v */
		mocks.ExpectCall(configuration, PeripheralLayer::Configuration::GetRimSize).Return(17);
		mocks.ExpectCall(configuration, PeripheralLayer::Configuration::GetTireAspect).Return(40);
		mocks.ExpectCall(configuration, PeripheralLayer::Configuration::GetTireWidth).Return(205);
		mocks.ExpectCall(configuration, PeripheralLayer::Configuration::GetFinalDriveRatio).Return(4.06f);
		mocks.ExpectCall(configuration, PeripheralLayer::Configuration::GetGearRatios).Return({ { 3.42f, 1.81f, 1.28f, 0.98f, 0.77f, PeripheralLayer::Configuration::UnavailableGear() } });
	}
};

struct ExpectedGear
{
	uint16_t rpm;
	uint32_t speed;
	uint32_t gear;
};

TEST(CalculatedGearModelTest, should_have_correct_initial_value)
{
	ApplicationLayer::Models::CalculatedGearModel gear(*configuration, *speed, *rpm);

	EXPECT_EQ(0, gear.GetRawValue());
	EXPECT_EQ("N", gear.GetFormattedValue());
}

TEST(CalculatedGearModelTest, should_calculate_correct_gear_for_rpm_and_speed)
{
	ApplicationLayer::Models::CalculatedGearModel gear(*configuration, *speed, *rpm);

	std::list<ExpectedGear> expected = { { 1000,  80, 1 }, { 1000, 152, 2 }, { 1000,  216, 3 }, { 1000,  282, 4 }, { 1000,  359, 5 },
	                                     { 2000, 160, 1 }, { 2000, 305, 2 }, { 2000,  432, 3 }, { 2000,  564, 4 }, { 2000,  718, 5 },
										 { 3000, 240, 1 }, { 3000, 458, 2 }, { 3000,  648, 3 }, { 3000,  846, 4 }, { 3000, 1077, 5 },
										 { 4000, 320, 1 }, { 4000, 611, 2 }, { 4000,  864, 3 }, { 4000, 1128, 4 }, { 4000, 1436, 5 }, 
										 { 5000, 400, 1 }, { 5000, 764, 2 }, { 5000, 1080, 3 }, { 5000, 1411, 4 }, { 5000, 1795, 5 }, 
										 { 6000, 480, 1 }, { 6000, 916, 2 }, { 6000, 1296, 3 }, { 6000, 1693, 4 }, { 6000, 2154, 5 } };

	for (auto&& e : expected)
	{
		mocks.ExpectCall(speed, ApplicationLayer::Models::Model::GetRawValue).Return(e.speed);
		mocks.ExpectCall(rpm, ApplicationLayer::Models::Model::GetRawValue).Return(e.rpm);

		gear.Update(0);

		EXPECT_EQ(e.gear, gear.GetRawValue());
		EXPECT_EQ(std::to_string(e.gear), gear.GetFormattedValue());
	}
}

TEST(CalculatedGearModelTest, should_calculate_correct_gear_when_speed_or_rpm_are_zero)
{
	ApplicationLayer::Models::CalculatedGearModel gear(*configuration, *speed, *rpm);

	std::list<ExpectedGear> expected = { { 0, 800, 0 }, { 4000, 0, 0 } };

	for (auto&& e : expected)
	{
		mocks.ExpectCall(speed, ApplicationLayer::Models::Model::GetRawValue).Return(e.speed);
		mocks.ExpectCall(rpm, ApplicationLayer::Models::Model::GetRawValue).Return(e.rpm);

		gear.Update(0);

		EXPECT_EQ(e.gear, gear.GetRawValue());
		EXPECT_EQ("N", gear.GetFormattedValue());
	}
}
