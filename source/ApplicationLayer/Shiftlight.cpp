#include "Shiftlight.h"

#include "Common/Math.h"

#include "HardwareLayer/LedDriver.h"

#include "PeripheralLayer/Color.h"
#include "PeripheralLayer/PatternPlayer.h"

#include "ApplicationLayer/Models/Model.h"

class BarFillPattern : public PeripheralLayer::LedPattern
{
public:
    void operator()(HardwareLayer::LedDriver& leds, uint32_t)
    {
        for (uint8_t i = 0; i < m_BarLength; ++i)
        {
            uint32_t color = i < 3 ? PeripheralLayer::Color::RGB(0, 20, 0).ToRGB() : PeripheralLayer::Color::RGB(20, 0, 0).ToRGB();
            leds.SetPixel(i, i < m_BarLength ? color : 0);
        }
    }

    void SetBarLength(uint8_t length)
    {
        m_BarLength = length;
    }

private:
    uint8_t m_BarLength = 0;
};

static PeripheralLayer::OffPattern LedOff;
static PeripheralLayer::BlinkPattern LedBlink(125);
static BarFillPattern LedBarFill;

ApplicationLayer::Shiftlight::Shiftlight(PeripheralLayer::PatternPlayer& patternPlayer, const ApplicationLayer::Models::Model& rpmModel)
    : m_RpmModel(rpmModel)
    , m_PatternPlayer(patternPlayer)
{
}

void ApplicationLayer::Shiftlight::Update(uint32_t now)
{
    if (m_RpmModel.GetRawValue() < m_LowerLimit)
    {
        m_PatternPlayer.Set(LedOff);
    }
    else if (m_RpmModel.GetRawValue() > m_UpperLimit)
    {
        m_PatternPlayer.Set(LedBlink);
    }
    else
    {
        m_PatternPlayer.Set(LedBarFill);
        LedBarFill.SetBarLength(Common::Math::Map(m_RpmModel.GetRawValue(), m_LowerLimit, m_UpperLimit - 100, 1, 8));
    }
}
