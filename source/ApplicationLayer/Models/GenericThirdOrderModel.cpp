#include "GenericThirdOrderModel.h"

#include <cmath>

ApplicationLayer::Models::GenericThirdOrderModel::GenericThirdOrderModel(float a, float b, float c, float d)
	: m_Poly({ { a, b, c, d } })
{
}

int32_t ApplicationLayer::Models::GenericThirdOrderModel::GetRawValue() const
{
	return m_Value;
}

const char* ApplicationLayer::Models::GenericThirdOrderModel::GetFormattedValue() const
{
	return nullptr;
}

void ApplicationLayer::Models::GenericThirdOrderModel::Update(uint32_t)
{
	float input = 0.f;
	m_Value = static_cast<int32_t>((m_Poly[0] * std::pow(input, 3) + m_Poly[1] * std::pow(input, 2) + m_Poly[2] * input + m_Poly[3]) * 100.f);
}
