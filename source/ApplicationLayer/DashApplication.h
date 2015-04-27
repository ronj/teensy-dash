#pragma once

#include "Common/TaskScheduler.h"

#include "ModelCollection.h"
#include "ModelUpdateTask.h"
#include "UserEventsTask.h"
#include "UserInterfaceTask.h"
#include "ViewCollection.h"

namespace PeripheralLayer
{
	class Peripherals;
}

namespace ApplicationLayer
{
	class DashApplication
	{
	public:
		DashApplication(PeripheralLayer::Peripherals& peripherals);

		bool IsRunning();
		void Eventloop();

	private:
		bool m_Running = true;

		ModelCollection m_Models;
		ViewCollection m_Views;

		ModelUpdateTask m_ModelUpdateTask;
		UserEventsTask m_UserEventsTask;
		UserInterfaceTask m_UITask;

		Common::TaskScheduler m_Scheduler;
	};
}
