#include "SDLDigitalPin.h"

#include <cinttypes>

namespace
{
	uint32_t ISR(uint32_t interval, void* data)
	{
		(*(reinterpret_cast<std::function<void()>*>(data)))();

		return interval;
	}
}

HardwareLayer::SDLDigitalPin::~SDLDigitalPin()
{
	SDL_RemoveTimer(m_TimerID);
}

void HardwareLayer::SDLDigitalPin::EnableInterrupt(InterruptType mode, std::function<void()> func)
{
	m_TimerID = SDL_AddTimer(10, ISR, &func);
}
