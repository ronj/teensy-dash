#pragma once

#include <cinttypes>

namespace HardwareLayer
{
    class RotaryEncoder
    {
    public:
        virtual bool NewValueAvailable() = 0;
        virtual int8_t GetDirection() = 0;
    };
}
