#include "SDLDigitalPin.h"

#include <cinttypes>

namespace
{
	uint32_t ISR(uint32_t interval, void* data)
	{
		HardwareLayer::SDLDigitalPin& pin = *static_cast<HardwareLayer::SDLDigitalPin*>(data);
		pin.m_ISR();

		return interval;
	}
}

HardwareLayer::SDLDigitalPin::~SDLDigitalPin()
{
	SDL_RemoveTimer(m_TimerID);
}

void HardwareLayer::SDLDigitalPin::EnableInterrupt(InterruptType mode, std::function<void()> isr)
{
	m_ISR = isr;
	m_TimerID = SDL_AddTimer(10, ISR, this);
}
