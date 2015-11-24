#include "yaffut.h"
#include "hippomocks.h"

#include "PeripheralLayer/FrequencyCounter.h"

#include "ApplicationLayer/Models/RPMModel.h"

struct RPMModelTest
{
	MockRepository mocks;
	PeripheralLayer::FrequencyCounter* frequencyCounter = mocks.Mock<PeripheralLayer::FrequencyCounter>();
};

TEST(RPMModelTest, should_have_correct_initial_value)
{
	ApplicationLayer::Models::RPMModel rpm(*frequencyCounter);

	EXPECT_EQ(0, rpm.GetRawValue());
	EXPECT_EQ("0", rpm.GetFormattedValue());
}

TEST(RPMModelTest, should_return_correct_rpm_based_on_measured_frequency)
{
	std::list<std::tuple<float, int32_t, std::string>> expected = { std::make_tuple(50.f, 2000, "2000"),
		                                                            std::make_tuple(60.f, 2400, "2400"),
			                                                        std::make_tuple(63.55f, 2542, "2500") };

	ApplicationLayer::Models::RPMModel rpm(*frequencyCounter);

	for (auto&& e : expected)
	{
		mocks.ExpectCall(frequencyCounter, PeripheralLayer::FrequencyCounter::GetFrequency).Return(std::get<0>(e));

		rpm.Update(0);

		EXPECT_EQ(std::get<1>(e), rpm.GetRawValue());
		EXPECT_EQ(std::get<2>(e), rpm.GetFormattedValue());
	}
}
