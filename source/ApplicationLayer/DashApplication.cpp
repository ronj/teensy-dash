#include "DashApplication.h"

#include "PeripheralLayer/Peripherals.h"
#include "PeripheralLayer/TimeProvider.h"

ApplicationLayer::DashApplication::DashApplication(PeripheralLayer::Peripherals& peripherals)
	: m_Models(peripherals)
	, m_ModelUpdateTask(m_Models)
	, m_UITask(peripherals.GetGraphicContext(), m_Models, peripherals.GetTimeProvider().TickCountMilliseconds())
{
	m_Scheduler.Add(m_ModelUpdateTask);
	m_Scheduler.Add(m_UITask);

	m_Scheduler.GetMillisecondCount = std::bind(&PeripheralLayer::TimeProvider::TickCountMilliseconds, peripherals.GetTimeProvider());
}

bool ApplicationLayer::DashApplication::IsRunning()
{
	return m_Running;
}

void ApplicationLayer::DashApplication::Eventloop()
{
	m_Scheduler.Run();
}
