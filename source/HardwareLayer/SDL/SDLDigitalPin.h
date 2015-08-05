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

        virtual void EnableInterrupt(InterruptType);
		virtual void DisableInterrupt();

	private:
		SDL_TimerID m_TimerID;
    };
}
