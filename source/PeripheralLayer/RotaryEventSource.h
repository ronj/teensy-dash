#pragma once

#include "EventSource.h"

namespace HardwareLayer
{
    class RotaryEncoder;
    class DigitalPin;
}

namespace PeripheralLayer
{
    class RotaryEventSource
        : public EventSource
    {
    public:
        RotaryEventSource(HardwareLayer::RotaryEncoder& encoder, HardwareLayer::DigitalPin& button);

        virtual bool EventAvailable();
        virtual EventType Get();

    private:
        HardwareLayer::RotaryEncoder& m_Encoder;
        HardwareLayer::DigitalPin& m_Button;

        volatile bool m_ButtonPressed = false;
    };
}
