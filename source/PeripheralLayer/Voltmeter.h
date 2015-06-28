#pragma once

#include <cinttypes>

namespace HardwareLayer
{
	class AnalogPin;
}

namespace PeripheralLayer
{
	class VoltageDivider;

	class Voltmeter
	{
	public:
		Voltmeter(const HardwareLayer::AnalogPin& pin, const VoltageDivider& divider);

		float GetVoltage() const;

	private:
		const HardwareLayer::AnalogPin& m_ADC;
		const VoltageDivider& m_Divider;
	};
}
