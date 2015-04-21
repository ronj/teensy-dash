#include "PitchModel.h"

#include "ConversionHelper.h"

#include "Common/Math.h"
#include "Common/Logger.h"

#include "PeripheralLayer/AccelerationAxis.h"

#include <cmath>

ApplicationLayer::Models::PitchModel::PitchModel(const PeripheralLayer::AccelerationAxis& xAxis, const PeripheralLayer::AccelerationAxis& yAxis, const PeripheralLayer::AccelerationAxis& zAxis)
	: m_XAxis(xAxis)
	, m_YAxis(yAxis)
	, m_ZAxis(zAxis)
    , m_PitchMilliDegrees(0)
{
}

int32_t ApplicationLayer::Models::PitchModel::GetRawValue() const
{
    return m_PitchMilliDegrees;
}

const char* ApplicationLayer::Models::PitchModel::GetFormattedValue() const
{
    static char formatted[4] = { 0 };

    itoa2(GetRawValue(), formatted, 10);

    return formatted;
}

void ApplicationLayer::Models::PitchModel::Update(uint32_t)
{
	float xAccel = m_XAxis.GetValue() / 1000.0f;
	float yAccel = m_YAxis.GetValue() / 1000.0f;
	float zAccel = m_ZAxis.GetValue() / 1000.0f;

    m_PitchMilliDegrees = static_cast<int32_t>(((std::atan2(xAccel, std::sqrt(yAccel * yAccel + zAccel * zAccel)) * 180.0f) / Common::Math::PI) * 1000.0f);
}
