#pragma once

#include "DigitalPin.h"

#include <SDL.h>
#include <functional>

namespace HardwareLayer
{
    class SDLDigitalPin
        : public DigitalPin
    {
    public:
		virtual ~SDLDigitalPin();
        virtual void EnableInterrupt(InterruptType mode, std::function<void()> isr);

        std::function<void()> m_ISR;

	private:
		SDL_TimerID m_TimerID;
    };
}
