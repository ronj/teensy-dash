#include "Application.h"

#include "HardwareLayer/SDLHardware.h"
#include "PeripheralLayer/Peripherals.h"
#include "ApplicationLayer/DashApplication.h"

int Application::Run()
{
	HardwareLayer::SDLHardware hardware;
	PeripheralLayer::Peripherals peripherals(hardware);
	ApplicationLayer::DashApplication application(peripherals);

	while (application.IsRunning())
	{
		application.Eventloop();
	}

	return 0;
}
