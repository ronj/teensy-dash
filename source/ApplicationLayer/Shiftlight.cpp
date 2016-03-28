#include "Shiftlight.h"

#include "Common/Math.h"

#include "HardwareLayer/LedDriver.h"

#include "PeripheralLayer/Color.h"
#include "PeripheralLayer/PatternPlayer.h"
#include "PeripheralLayer/LedPatterns.h"

#include "ApplicationLayer/Models/Model.h"

static PeripheralLayer::OffPattern LedOff;
static PeripheralLayer::BlinkPattern LedBlink(125);
static PeripheralLayer::BarFillPattern LedBarFill;

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
