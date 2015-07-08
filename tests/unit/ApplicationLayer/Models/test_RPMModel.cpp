#include "yaffut.h"
#include "hippomocks.h"

#include "PeripheralLayer/PulseCounter.h"

#include "ApplicationLayer/Models/RPMModel.h"

struct RPMModelTest
{
	MockRepository mocks;
	PeripheralLayer::PulseCounter* pulseCounter = mocks.Mock<PeripheralLayer::PulseCounter>();
};

TEST(RPMModelTest, should_have_correct_initial_value)
{
	ApplicationLayer::Models::RPMModel rpm(*pulseCounter);

	EXPECT_EQ(0, rpm.GetRawValue());
	EXPECT_EQ("0", rpm.GetFormattedValue());
}
