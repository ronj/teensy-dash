#include "RandomValueModel.h"

#include "ConversionHelper.h"

#ifndef BUILD_FOR_EMULATOR
	#include "Common/ArduinoWrapper.h"
#else
	#include <cstdlib>
	#define random(from, to) from + (rand() % (int)(to - from + 1))
#endif

ApplicationLayer::Models::RandomValueModel::RandomValueModel(int32_t from, int32_t to)
	: m_Value(0)
	, m_From(from)
	, m_To(to)
{
}

int32_t ApplicationLayer::Models::RandomValueModel::GetRawValue() const
{
	return m_Value;
}

const char* ApplicationLayer::Models::RandomValueModel::GetFormattedValue() const
{
	static char formatted[5] = { 0 };
	int32_t rawValue = GetRawValue();

	if (rawValue > 10)
	{
		itoa2(rawValue / 10, formatted, 10);
		formatted[2] = '.';
		itoa2(rawValue % 10, formatted + 3, 10);
	}
	else
	{
		itoa2(rawValue, formatted, 10);
	}

	return formatted;
}

void ApplicationLayer::Models::RandomValueModel::Update(uint32_t)
{
	m_Value = random(m_From, m_To);
}
