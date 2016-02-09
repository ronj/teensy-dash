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

	snprintf(formatted, 5, "%" PRIu32 ".%" PRIu32, rawValue / 100, (rawValue % 100) / 10);

	return formatted;
}

void ApplicationLayer::Models::VoltageModel::Update(uint32_t)
{
	m_Value = static_cast<int32_t>(m_Meter.GetVoltage() * 100);
}
