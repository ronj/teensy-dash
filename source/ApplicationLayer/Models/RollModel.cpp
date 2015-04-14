#include "RollModel.h"

#include "ConversionHelper.h"

#include "Common/Math.h"
#include "Common/Logger.h"

#include "PeripheralLayer/AccelerationAxis.h"

ApplicationLayer::Models::RollModel::RollModel(const PeripheralLayer::AccelerationAxis& yAxis, const PeripheralLayer::AccelerationAxis& zAxis)
	: m_YAxis(yAxis)
	, m_ZAxis(zAxis)
    , m_RollMilliDegrees(0)
{
}

int32_t ApplicationLayer::Models::RollModel::GetRawValue() const
{
    return m_RollMilliDegrees;
}

const char* ApplicationLayer::Models::RollModel::GetFormattedValue() const
{
    static char formatted[4] = { 0 };

    itoa2(GetRawValue(), formatted, 10);

    return formatted;
}

void ApplicationLayer::Models::RollModel::Update(uint32_t)
{
	float yAccel = m_YAxis.GetValue() / 1000.0f;
	float zAccel = m_ZAxis.GetValue() / 1000.0f;

    m_RollMilliDegrees = ((std::atan2(-yAccel, zAccel) * 180.0f) / Common::Math::PI) * 1000.0f;
}
