#include "PulseDuration.h"

#include "Common/DisableInterruptContext.h"

#include "HardwareLayer/DigitalPin.h"

#include "PeripheralLayer/TimeProvider.h"

namespace
{
	volatile uint32_t risingEdgeStartTime = 0;
}

PeripheralLayer::PulseDuration::PulseDuration(HardwareLayer::DigitalPin& pin, PeripheralLayer::TimeProvider& time)
	: m_Pin(pin)
	, m_Time(time)
{
	pin.OnInterrupt = [this]() { Process(); };
	pin.EnableInterrupt(HardwareLayer::InterruptType::Change);
}

uint32_t PeripheralLayer::PulseDuration::GetCount()
{
	return Common::Atomic::CopyAndResetValue(m_Count);
}

uint32_t PeripheralLayer::PulseDuration::GetDuration()
{
	return Common::Atomic::CopyAndResetValue(m_Duration);
}

void PeripheralLayer::PulseDuration::GetCountAndDuration(uint32_t& count, uint32_t& duration)
{
	Common::DisableInterruptContext disable;

	count = m_Count;
	duration = m_Duration;

	m_Count = 0;
	m_Duration = 0;
}

void PeripheralLayer::PulseDuration::Process()
{
	if (m_Pin.Read() == 1)
	{
		risingEdgeStartTime = m_Time.TickCountMicroseconds();
	}
	else
	{
		m_Duration += m_Time.TickCountMicroseconds() - risingEdgeStartTime;
		++m_Count;
	}
}
