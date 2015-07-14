#include "DashApplication.h"

#include "PeripheralLayer/Peripherals.h"
#include "PeripheralLayer/TimeProvider.h"

ApplicationLayer::DashApplication::DashApplication(PeripheralLayer::Peripherals& peripherals)
	: m_Peripherals(peripherals)
	, m_Models(peripherals)
	, m_Views(m_Models)
	, m_ModelUpdateTask(m_Models, peripherals.GetTimeProvider().TickCountMilliseconds())
	, m_UserEventsTask(peripherals)
	, m_UITask(peripherals.GetGraphicContext(), m_Views, peripherals.GetTimeProvider().TickCountMilliseconds())
	, m_Shiftlight(peripherals.GetLedContext(), m_Models.GetRPMModel())
{
	m_Scheduler.Add(m_UserEventsTask);
	m_Scheduler.Add(m_ModelUpdateTask);
	m_Scheduler.Add(m_UITask);

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
	uint32_t now = m_Peripherals.GetTimeProvider().TickCountMilliseconds();

	if (!m_Scheduler.Run(now))
	{
		m_Peripherals.GetPowerManagement().Idle();
	}

	m_Shiftlight.Update(now);

	if (m_Models.GetRPMModel().GetRawValue() == 0)
	{
		m_IsPoweredDown = true;

		m_Peripherals.GetPowerManagement().PowerDownPeripherals();
		m_Peripherals.GetPowerManagement().LowPowerSleep();
	}
	else if (m_Models.GetRPMModel().GetRawValue() > 0 && m_IsPoweredDown)
	{
		m_IsPoweredDown = false;

		m_Peripherals.GetPowerManagement().PowerUpPeripherals();
	}

	m_Peripherals.GetTimeProvider().Sleep(25);
}
