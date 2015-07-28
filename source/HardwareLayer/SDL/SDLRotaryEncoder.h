#pragma once

#include "RotaryEncoder.h"

#include <SDL.h>

namespace HardwareLayer
{
	class SDLRotaryEncoder
		: public RotaryEncoder
	{
	public:
        virtual bool NewValueAvailable();
        virtual int8_t GetDirection();

    private:
        SDL_Event m_Event;
	};
}
