#include "SDLTimer.h"

#include <SDL.h>

uint32_t HardwareLayer::SDLTimer::TickCountMilliseconds() const
{
	return SDL_GetTicks();
}

uint32_t HardwareLayer::SDLTimer::TickCountMicroseconds() const
{
	return SDL_GetTicks();
}

void HardwareLayer::SDLTimer::Sleep(uint32_t milliseconds) const
{
	SDL_Delay(milliseconds);
}
