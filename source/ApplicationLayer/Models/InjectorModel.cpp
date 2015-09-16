#include "InjectorModel.h"

#include "PeripheralLayer/PulseDuration.h"

ApplicationLayer::Models::InjectorModel::InjectorModel(PeripheralLayer::PulseDuration& pulseDuration)
	: m_PulseDuration(pulseDuration)
{
}

int32_t ApplicationLayer::Models::InjectorModel::GetRawValue() const
{
    return m_InjectorOpen;
}

const char* ApplicationLayer::Models::InjectorModel::GetFormattedValue() const
{
	return nullptr;
}

void ApplicationLayer::Models::InjectorModel::Update(uint32_t)
{
	m_InjectorOpen = m_PulseDuration.GetDuration();
}
