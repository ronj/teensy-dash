#include "TirePressureModel.h"

#include "ConversionHelper.h"

#include "Common/Logger.h"

#include <algorithm>
#include <limits>

ApplicationLayer::Models::TirePressureModel::TirePressureModel()
    : m_PackedValues(std::numeric_limits<uint32_t>::max())
{
}

int32_t ApplicationLayer::Models::TirePressureModel::GetRawValue() const
{
    return m_PackedValues;
}

void ApplicationLayer::Models::TirePressureModel::Update(uint32_t)
{
}

void ApplicationLayer::Models::TirePressureModel::UnpackValues(int32_t input, uint16_t& frontLeft, uint16_t& frontRight, uint16_t& rearLeft, uint16_t& rearRight)
{
	frontLeft = ((input >> 24) & 0xFF) * 2;
	frontRight = ((input >> 16) & 0xFF) * 2;
	rearLeft = ((input >> 8) & 0xFF) * 2;
	rearRight = (input & 0xFF) * 2;
}
