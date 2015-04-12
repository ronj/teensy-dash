#include "Application.h"

#include "HardwareLayer/TeensyHardware.h"
#include "PeripheralLayer/Peripherals.h"
#include "ApplicationLayer/DashApplication.h"

int Application::Run()
{
	HardwareLayer::TeensyHardware hardware;
	PeripheralLayer::Peripherals peripherals(hardware);
	ApplicationLayer::DashApplication application(peripherals);

	while (application.IsRunning())
	{
		application.Eventloop();
	}

	return 0;
}
