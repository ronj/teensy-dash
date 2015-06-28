#include "Voltmeter.h"

#include "HardwareLayer/AnalogPin.h"
#include "VoltageDivider.h"

PeripheralLayer::Voltmeter::Voltmeter(const HardwareLayer::AnalogPin& pin, const VoltageDivider& divider)
	: m_ADC(pin)
	, m_Divider(divider)
{
}

float PeripheralLayer::Voltmeter::GetVoltage() const
{
	return m_Divider.GetVoltage(m_ADC.Read());
}
