#include "VoltageModel.h"

#include "ConversionHelper.h"

#include "PeripheralLayer/Voltmeter.h"

ApplicationLayer::Models::VoltageModel::VoltageModel(const PeripheralLayer::Voltmeter& meter)
	: m_Meter(meter)
	, m_Value(0)
{
}

int32_t ApplicationLayer::Models::VoltageModel::GetRawValue() const
{
	return m_Value;
}

const char* ApplicationLayer::Models::VoltageModel::GetFormattedValue() const
{
	static char formatted[5] = { 0 };

	int32_t rawValue = GetRawValue();
	int16_t integerPart = rawValue / 100;
	int16_t fractionalPart = rawValue % 100;

	if (integerPart > 10)
	{
		itoa2(integerPart, formatted, 10);
		formatted[2] = '.';
		itoa2(fractionalPart, formatted + 3, 10);
	}
	else
	{
		itoa2(integerPart, formatted, 10);
		formatted[1] = '.';
		itoa2(fractionalPart, formatted + 2, 10);
	}

	return formatted;
}

void ApplicationLayer::Models::VoltageModel::Update(uint32_t)
{
	m_Value = static_cast<int32_t>(m_Meter.GetVoltage() * 100);
}
