#pragma once

#include "DigitalPin.h"

#include <SDL.h>

namespace HardwareLayer
{
    class SDLDigitalPin
        : public DigitalPin
    {
    public:
		virtual ~SDLDigitalPin();
        virtual void EnableInterrupt(InterruptType mode, std::function<void()> func);

	private:
		SDL_TimerID m_TimerID;
    };
}
