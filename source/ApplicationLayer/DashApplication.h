#pragma once

#include "Common/TaskScheduler.h"

#include "ModelCollection.h"
#include "ModelUpdateTask.h"
#include "Shiftlight.h"
#include "UserEventsTask.h"
#include "UserInterfaceTask.h"
#include "ViewCollection.h"

namespace PeripheralLayer
{
	class Peripherals;
}

namespace ApplicationLayer
{
	enum class ApplicationState : uint8_t
	{
		Initial,
		EngineStart,
		EngineRunning,
		EngineStop,
		Sleep
	};

	class DashApplication
	{
	public:
		DashApplication(PeripheralLayer::Peripherals& peripherals);

		bool IsRunning();
		void Eventloop();

	private:
		void SetState(ApplicationState newState);

	private:
		static const uint32_t SHUTDOWN_THRESHOLD_AFTER_RPM_LOSS = 3000;

		ApplicationState m_State = ApplicationState::Initial;
		bool m_Running = true;
		uint32_t m_RPMLossTimestamp = 0;

		PeripheralLayer::Peripherals& m_Peripherals;

		ModelCollection m_Models;
		ViewCollection m_Views;

		ModelUpdateTask m_ModelUpdateTask;
		UserEventsTask m_UserEventsTask;
		UserInterfaceTask m_UITask;

		Common::TaskScheduler m_Scheduler;

		Shiftlight m_Shiftlight;
	};
}
