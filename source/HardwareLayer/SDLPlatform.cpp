#include "SDLPlatform.h"

#include <SDL.h>

HardwareLayer::SDLPlatform::~SDLPlatform()
{
	SDL_Quit();
}

void HardwareLayer::SDLPlatform::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//throw std::runtime_error("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
	}
}
