#include "DashApplication.h"

#include "Common/Logger.h"

#include "PeripheralLayer/Peripherals.h"
#include "PeripheralLayer/TimeProvider.h"

ApplicationLayer::DashApplication::DashApplication(PeripheralLayer::Peripherals& peripherals)
	: m_Peripherals(peripherals)
	, m_Models(peripherals)
	, m_Views(m_Models)
	, m_ModelUpdateTask(m_Models, peripherals.GetTimeProvider().TickCountMilliseconds())
	, m_UserEventsTask(peripherals)
	, m_UITask(peripherals.GetGraphicContext(), m_Views, peripherals.GetTimeProvider().TickCountMilliseconds())
	, m_Shiftlight(peripherals.GetPatternPlayer(), m_Models.GetRPMModel())
{
	LOG_METHOD_ENTRY;

	m_Scheduler.Add(m_UserEventsTask);
	m_Scheduler.Add(m_ModelUpdateTask);
	m_Scheduler.Add(m_UITask);

	m_UserEventsTask.OnNext = std::bind(&ApplicationLayer::UserInterfaceTask::NextScreen, &m_UITask);
	m_UserEventsTask.OnPrevious = std::bind(&ApplicationLayer::UserInterfaceTask::PreviousScreen, &m_UITask);
	m_UserEventsTask.OnShortPress = std::bind(&ApplicationLayer::UserInterfaceTask::NextScreen, &m_UITask);
	m_UserEventsTask.OnQuery = std::bind(&ApplicationLayer::UserInterfaceTask::QueryScreen, &m_UITask);
	m_UserEventsTask.OnQuit = [this]() { m_Running = false; };
}

bool ApplicationLayer::DashApplication::IsRunning()
{
	return m_Running;
}

void ApplicationLayer::DashApplication::Eventloop()
{
	uint32_t now = m_Peripherals.GetTimeProvider().TickCountMilliseconds();

	m_Shiftlight.Update(now);

    m_Peripherals.GetPatternPlayer().Update(now);

	m_Scheduler.Run(now);

	HandlePowerMode(now);
}

void ApplicationLayer::DashApplication::HandlePowerMode(uint32_t now)
{
	uint32_t rpm = m_Models.GetRPMModel().GetRawValue();

	if ((rpm == 0) && (m_RPMLossTimestamp == 0))
	{
		m_RPMLossTimestamp = now;
	}
	else if (rpm > 0)
	{
		m_RPMLossTimestamp = 0;

		if (m_IsPoweredDown)
		{
			m_IsPoweredDown = false;
			m_Peripherals.GetPowerManagement().PowerUpPeripherals();
		}
	}

	if (m_RPMLossTimestamp &&
	   (now - m_RPMLossTimestamp > SHUTDOWN_THRESHOLD_AFTER_RPM_LOSS))
	{
		m_IsPoweredDown = true;

		m_Peripherals.GetPowerManagement().PowerDownPeripherals();
		m_Peripherals.GetPowerManagement().LowPowerSleep();
	}

	if (m_IsPoweredDown)
	{
		m_Peripherals.GetTimeProvider().Sleep(25);
	}
}
