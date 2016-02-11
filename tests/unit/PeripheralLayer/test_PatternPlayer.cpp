#include "yaffut.h"
#include "hippomocks.h"

#include "PeripheralLayer/PatternPlayer.h"

#include "HardwareLayer/LedDriver.h"

struct PatternPlayerTest
{
    MockRepository mocks;
    HardwareLayer::LedDriver* ledDriver = mocks.Mock<HardwareLayer::LedDriver>();
};

TEST(PatternPlayerTest, should_clear_leds_on_idle_pattern)
{
    PeripheralLayer::PatternPlayer player(*ledDriver);

    mocks.ExpectCall(ledDriver, HardwareLayer::LedDriver::Clear);
    mocks.ExpectCall(ledDriver, HardwareLayer::LedDriver::Update);

    PeripheralLayer::OffPattern off;

    player.Set(off);
    player.Update(0);
}
