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

	switch (m_State)
	{
		case ApplicationState::Initial:
			// Read config from non-volatile memory and go to sleep
		    // state, which keeps checking if the engine is running.
			m_Peripherals.GetPowerManagement().PowerDownPeripherals();
			SetState(ApplicationState::Sleep);
			break;

		case ApplicationState::EngineStart:
			// Show splash-screen and after time-out go to running
			// state.
			m_RPMLossTimestamp = 0;
			m_Peripherals.GetPowerManagement().PowerUpPeripherals();
			SetState(ApplicationState::EngineRunning);
			break;

		case ApplicationState::EngineRunning:
			// Update all tasks by running the scheduler.
			m_Shiftlight.Update(now);
			m_Peripherals.GetPatternPlayer().Update(now);

			m_Scheduler.Run(now);

			if (m_Models.GetRPMModel().GetRawValue() == 0 && m_RPMLossTimestamp == 0)
			{
				m_RPMLossTimestamp = now;
			}
			else if (m_Models.GetRPMModel().GetRawValue() > 0)
			{
				m_RPMLossTimestamp = 0;
			}

			if (m_RPMLossTimestamp &&
	   		   (now - m_RPMLossTimestamp > SHUTDOWN_THRESHOLD_AFTER_RPM_LOSS))
			{
				SetState(ApplicationState::EngineStop);
			}
			break;

		case ApplicationState::EngineStop:
			// Write updated info to non-volatile memory, show trip
			// summary and after time-out go to sleep state.
			m_Peripherals.GetPowerManagement().PowerDownPeripherals();
			SetState(ApplicationState::Sleep);
			break;

		case ApplicationState::Sleep:
			m_ModelUpdateTask.Run(now);

			if (m_Models.GetRPMModel().GetRawValue() > 0)
			{
				SetState(ApplicationState::EngineStart);
			}
			else
			{
				m_Peripherals.GetPowerManagement().LowPowerSleep();
			}
			break;

		default:
			Common::Logger::Get().LogLine("Unknown application state.");
			m_Running = false;
	}
}

void ApplicationLayer::DashApplication::SetState(ApplicationState newState)
{
	m_State = newState;
}
