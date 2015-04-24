#pragma once

#include "DigitalPin.h"

namespace HardwareLayer
{
    class TeensyDigitalPin
        : public DigitalPin
    {
    public:
        TeensyDigitalPin(const uint8_t pin);

        virtual void EnableInterrupt(InterruptType edge);

    private:
        const uint8_t m_Pin;
    };
}
