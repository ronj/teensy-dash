#pragma once

#include "DigitalPin.h"

namespace HardwareLayer
{
    class TeensyDigitalPin
        : public DigitalPin
    {
    public:
        TeensyDigitalPin(const uint8_t pin);
        virtual ~TeensyDigitalPin();

        virtual void EnableInterrupt(InterruptType mode, std::function<void()> isr);

    private:
        const uint8_t m_Pin;
    };
}
