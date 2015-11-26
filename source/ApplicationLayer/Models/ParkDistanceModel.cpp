#include "ParkDistanceModel.h"

#include "ConversionHelper.h"

#include "PeripheralLayer/ParkDistanceDecoder.h"

#include "Common/Logger.h"

#include <algorithm>
#include <limits>

ApplicationLayer::Models::ParkDistanceModel::ParkDistanceModel(const PeripheralLayer::ParkDistanceDecoder& parkDistanceDecoder)
    : m_ParkDistanceDecoder(parkDistanceDecoder)
    , m_PackedValues(std::numeric_limits<uint32_t>::max())
{
}

int32_t ApplicationLayer::Models::ParkDistanceModel::GetRawValue() const
{
    return m_PackedValues;
}

const char* ApplicationLayer::Models::ParkDistanceModel::GetFormattedValue() const
{
    static char formatted[5] = { 0 };
    
    uint8_t a, b, c, d;
    UnpackValues(m_PackedValues, a, b, c, d);

    uint8_t minDistance = std::min({ a, b, c, d });

    if (minDistance < std::numeric_limits<uint8_t>::max())
    {
        snprintf(formatted, 5, "%d.%02d", minDistance / 100, minDistance % 100);
    }
    else
    {
        snprintf(formatted, 5, "-.--");
    }

    return formatted;
}

void ApplicationLayer::Models::ParkDistanceModel::Update(uint32_t)
{
    m_PackedValues = m_ParkDistanceDecoder.GetPackedDistances();
}

void ApplicationLayer::Models::ParkDistanceModel::UnpackValues(int32_t input, uint8_t& sensorA, uint8_t& sensorB, uint8_t& sensorC, uint8_t& sensorD)
{
    sensorA = (input >> 24) & 0xFF;
    sensorB = (input >> 16) & 0xFF;
    sensorC = (input >> 8) & 0xFF;
    sensorD = input & 0xFF;
}
