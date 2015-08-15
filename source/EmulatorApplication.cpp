#include "Application.h"

#include "HardwareLayer/SDL/SDLHardware.h"
#include "PeripheralLayer/Peripherals.h"
#include "ApplicationLayer/DashApplication.h"

int Application::Run()
{
	HardwareLayer::SDLHardware hardware;
	PeripheralLayer::Peripherals peripherals(hardware);
	ApplicationLayer::DashApplication application(peripherals);

	LogSoftwareVersion();

	while (application.IsRunning())
	{
		application.Eventloop();
		hardware.GetPlatform().KickWatchdog();
	}

	return 0;
}
