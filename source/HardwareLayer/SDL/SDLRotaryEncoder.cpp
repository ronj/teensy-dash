#include "SDLRotaryEncoder.h"

bool HardwareLayer::SDLRotaryEncoder::NewValueAvailable()
{
    return SDL_PollEvent(&m_Event) >= 1 ? true : false;
}

int8_t HardwareLayer::SDLRotaryEncoder::GetDirection()
{
    switch (m_Event.type)
    {
    case SDL_KEYUP:
        if (m_Event.key.keysym.sym == SDLK_LEFT)
            return 1;
        else if (m_Event.key.keysym.sym == SDLK_RIGHT)
            return -1;
    }

    return 0;
}
