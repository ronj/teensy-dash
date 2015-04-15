#include "SDLPlatform.h"

#include "Common/Logger.h"

#include <SDL.h>

HardwareLayer::SDLPlatform::~SDLPlatform()
{
	SDL_Quit();
}

void HardwareLayer::SDLPlatform::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::string error = "SDL could not initialize! SDL_Error: " + std::string(SDL_GetError());
		Common::Logger::Get().Log(error.c_str());
	}
}
