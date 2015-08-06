#include "ParkDistanceModel.h"

#include "PeripheralLayer/ParkDistanceDecoder.h"

#include <algorithm>

ApplicationLayer::Models::ParkDistanceModel::ParkDistanceModel(const PeripheralLayer::ParkDistanceDecoder& parkDistanceDecoder)
	: m_ParkDistanceDecoder(parkDistanceDecoder)
{
}

int32_t ApplicationLayer::Models::ParkDistanceModel::GetRawValue() const
{
	return m_PackedValues;
}

const char* ApplicationLayer::Models::ParkDistanceModel::GetFormattedValue() const
{
	static char formatted[4] = { 0 };
	
	uint8_t a, b, c, d;
	UnpackValues(m_PackedValues, a, b, c, d);

	uint8_t minDistance = std::min({ a, b, c, d });
	sprintf(formatted, "%d.%02d", minDistance / 100, minDistance % 100);

	return formatted;
}

void ApplicationLayer::Models::ParkDistanceModel::Update(uint32_t now)
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
