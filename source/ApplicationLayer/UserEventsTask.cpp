#include "UserEventsTask.h"

#include "PeripheralLayer/Peripherals.h"

ApplicationLayer::UserEventsTask::UserEventsTask(PeripheralLayer::Peripherals& peripherals)
{
	m_EventSources.Add(peripherals.GetRotaryEventSource());
	m_EventSources.Add(peripherals.GetSerialEventSource());
}

bool ApplicationLayer::UserEventsTask::CanRun(uint32_t)
{
	for (auto&& e : m_EventSources)
	{
		if (e.EventAvailable()) return true;
	}

	return false;
}

void ApplicationLayer::UserEventsTask::Run(uint32_t)
{
	for (auto&& e : m_EventSources)
	{
		switch (e.Get())
		{
		case PeripheralLayer::EventType::Next :
			CallWrapper(OnNext);
			break;
		case PeripheralLayer::EventType::Previous :
			CallWrapper(OnPrevious);
			break;
		case PeripheralLayer::EventType::ShortPress:
			CallWrapper(OnShortPress);
			break;
		case PeripheralLayer::EventType::LongPress:
			CallWrapper(OnLongPress);
			break;
		case PeripheralLayer::EventType::Query:
			CallWrapper(OnQuery);
			break;
		case PeripheralLayer::EventType::Quit:
			CallWrapper(OnQuit);
			break;
		default:
			break;
		}
	}
}
