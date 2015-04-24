#include "SDLPlatform.h"

#include "Common/Logger.h"

#include <SDL.h>

HardwareLayer::SDLPlatform::SDLPlatform()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		std::string error = "SDL could not initialize! SDL_Error: " + std::string(SDL_GetError());
		Common::Logger::Get().LogLine(error.c_str());
	}
}

HardwareLayer::SDLPlatform::~SDLPlatform()
{
	SDL_Quit();
}

void HardwareLayer::SDLPlatform::Init()
{
}
