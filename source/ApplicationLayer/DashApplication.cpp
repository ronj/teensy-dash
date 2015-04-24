#include "DashApplication.h"

#include "PeripheralLayer/Peripherals.h"
#include "PeripheralLayer/TimeProvider.h"

ApplicationLayer::DashApplication::DashApplication(PeripheralLayer::Peripherals& peripherals)
	: m_Models(peripherals)
	, m_ModelUpdateTask(m_Models, peripherals.GetTimeProvider().TickCountMilliseconds())
	, m_UserEventsTask(peripherals)
	, m_UITask(peripherals.GetGraphicContext(), m_Models, peripherals.GetTimeProvider().TickCountMilliseconds())
{
	m_Scheduler.Add(m_ModelUpdateTask);
	m_Scheduler.Add(m_UserEventsTask);
	m_Scheduler.Add(m_UITask);

	m_Scheduler.GetMillisecondCount = std::bind(&PeripheralLayer::TimeProvider::TickCountMilliseconds, &peripherals.GetTimeProvider());

	m_UserEventsTask.OnNext = std::bind(&ApplicationLayer::UserInterfaceTask::NextScreen, &m_UITask);
	m_UserEventsTask.OnPrevious = std::bind(&ApplicationLayer::UserInterfaceTask::PreviousScreen, &m_UITask);
	m_UserEventsTask.OnQuit = [this]() { m_Running = false; };
}

bool ApplicationLayer::DashApplication::IsRunning()
{
	return m_Running;
}

void ApplicationLayer::DashApplication::Eventloop()
{
	m_Scheduler.Run();
}
