#include "WheelTickModel.h"

#include "PeripheralLayer/PulseCounter.h"

#include "ConversionHelper.h"

ApplicationLayer::Models::WheelTickModel::WheelTickModel(PeripheralLayer::PulseCounter& pulseCounter)
	: m_PulseCounter(pulseCounter)
{
}

int32_t ApplicationLayer::Models::WheelTickModel::GetRawValue() const
{
	return m_CurrentWheelTicks;
}

const char* ApplicationLayer::Models::WheelTickModel::GetFormattedValue() const
{
	return nullptr;
}

void ApplicationLayer::Models::WheelTickModel::Update(uint32_t)
{
	m_CurrentWheelTicks = m_PulseCounter.GetCount();
}
