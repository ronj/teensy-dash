#include "AccelerationModel.h"

#include "ConversionHelper.h"

#include "PeripheralLayer/AccelerationAxis.h"

ApplicationLayer::Models::AccelerationModel::AccelerationModel(const PeripheralLayer::AccelerationAxis& axis)
	: m_Axis(axis)
    , m_AccelerationMilliG(0)
{
}

int32_t ApplicationLayer::Models::AccelerationModel::GetRawValue() const
{
    return m_AccelerationMilliG;
}

const char* ApplicationLayer::Models::AccelerationModel::GetFormattedValue() const
{
    static char formatted[4] = { 0 };

    itoa2(GetRawValue(), formatted, 10);

    return formatted;
}

void ApplicationLayer::Models::AccelerationModel::Update(uint32_t)
{
    m_AccelerationMilliG = m_Axis.GetValue();
}
