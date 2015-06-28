#include "VoltageDivider.h"

PeripheralLayer::VoltageDivider::VoltageDivider(uint32_t resistorOneValue, uint32_t resistorTwoValue, float referenceVoltage)
	: m_Denominator(static_cast<float>(resistorTwoValue) / (resistorOneValue + resistorTwoValue))
	, m_ReferenceVoltage(referenceVoltage)
{
}

float PeripheralLayer::VoltageDivider::GetVoltage(uint16_t adcCount) const
{
	float voltage = (adcCount * m_ReferenceVoltage) / m_ADCResolution;
	return voltage / m_Denominator;
}
