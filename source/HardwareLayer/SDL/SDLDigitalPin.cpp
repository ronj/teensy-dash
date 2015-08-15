#include "SDLDigitalPin.h"

#include <cinttypes>

namespace
{
	uint32_t ISR(uint32_t interval, void* data)
	{
		HardwareLayer::SDLDigitalPin& pin = *static_cast<HardwareLayer::SDLDigitalPin*>(data);
		pin.OnInterrupt();

		return interval;
	}
}

HardwareLayer::SDLDigitalPin::~SDLDigitalPin()
{
	DisableInterrupt();
}

uint8_t HardwareLayer::SDLDigitalPin::Read()
{
	return 0;
}

void HardwareLayer::SDLDigitalPin::EnableInterrupt(InterruptType)
{
	m_TimerID = SDL_AddTimer(10, ISR, this);
}

void HardwareLayer::SDLDigitalPin::DisableInterrupt()
{
	SDL_RemoveTimer(m_TimerID);
}
