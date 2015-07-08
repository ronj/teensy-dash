#include "Application.h"

#ifdef BUILD_FOR_EMULATOR
	#include <SDL.h>
#endif

int main(int, char**)
{
	Application app;
	return app.Run();
}
