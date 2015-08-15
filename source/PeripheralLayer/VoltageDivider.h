#pragma once

#include <cinttypes>

namespace PeripheralLayer
{
	class VoltageDivider
	{
	public:
		VoltageDivider(uint32_t resistorOneValue, uint32_t resistorTwoValue, float referenceVoltage);

		float GetVoltage(uint16_t adcCount) const;

	private:
		float m_Denominator;
		float m_ReferenceVoltage;
		const uint16_t m_ADCResolution = 1023u;
	};
}
