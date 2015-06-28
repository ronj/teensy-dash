#include "VoltageModel.h"

#include "ConversionHelper.h"

#include "Common/Logger.h"

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

	itoa2(rawValue / 100, formatted, 10);
	formatted[1] = '.';
	itoa2(rawValue % 100, formatted + 2, 10);

	return formatted;
}

void ApplicationLayer::Models::VoltageModel::Update(uint32_t)
{
	Common::Logger::Get().Log(m_Meter.GetVoltage());

	m_Value = static_cast<int32_t>(m_Meter.GetVoltage() * 100);
}
