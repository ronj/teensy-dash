#include "Application.h"

#ifdef BUILD_FOR_EMULATOR
	#include <SDL.h>
#else
	extern "C" int _kill(int, int)
	{
		return 0;
	}

	extern "C" int _getpid()
	{
		return 0;
	}
#endif

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	Application app;
	return app.Run();
}
