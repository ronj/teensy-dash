#pragma once

#include "Common/TaskScheduler.h"

#include "ModelCollection.h"
#include "ModelUpdateTask.h"
#include "UserInterfaceTask.h"

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

		ModelUpdateTask m_ModelUpdateTask;
		UserInterfaceTask m_UITask;

		Common::TaskScheduler m_Scheduler;
	};
}
