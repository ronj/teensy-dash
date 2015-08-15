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
