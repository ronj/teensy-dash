#include "InjectorModel.h"

#include "PeripheralLayer/Configuration.h"
#include "PeripheralLayer/PulseDuration.h"

ApplicationLayer::Models::InjectorModel::InjectorModel(PeripheralLayer::PulseDuration& pulseDuration, const PeripheralLayer::Configuration& configuration)
	: m_Configuration(configuration)
	, m_PulseDuration(pulseDuration)
{
}

int32_t ApplicationLayer::Models::InjectorModel::GetRawValue() const
{
    return m_InjectorOpen;
}

void ApplicationLayer::Models::InjectorModel::Update(uint32_t)
{
	uint32_t count = 0;
	uint32_t duration = 0;

	m_PulseDuration.GetCountAndDuration(count, duration);

	m_InjectorOpen = duration - (count * m_Configuration.GetInjectorMechanicalDelay());
}
