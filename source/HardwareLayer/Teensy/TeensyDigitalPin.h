#pragma once

#include "DigitalPin.h"

namespace HardwareLayer
{
    class TeensyDigitalPin
        : public DigitalPin
    {
    public:
        TeensyDigitalPin(const uint8_t pin);
        TeensyDigitalPin(const uint8_t pin, PinType type);

        virtual ~TeensyDigitalPin();

		virtual uint8_t Read();

        virtual void EnableInterrupt(InterruptType mode);
		virtual void DisableInterrupt();

    private:
        const uint8_t m_Pin;
    };
}
