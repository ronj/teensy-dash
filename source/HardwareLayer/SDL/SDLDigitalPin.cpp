#include "SDLDigitalPin.h"

#include <cinttypes>

namespace
{
	uint32_t ISR(uint32_t interval, void* data)
	{
		HardwareLayer::SDLDigitalPin& pin = *(reinterpret_cast<HardwareLayer::SDLDigitalPin*>(data));

		pin.OnInterrupt();

		return interval;
	}
}

HardwareLayer::SDLDigitalPin::~SDLDigitalPin()
{
	SDL_RemoveTimer(m_TimerID);
}

void HardwareLayer::SDLDigitalPin::EnableInterrupt(InterruptType)
{
	m_TimerID = SDL_AddTimer(10, ISR, this);
}
