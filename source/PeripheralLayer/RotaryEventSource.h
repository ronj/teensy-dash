#pragma once

#include "EventSource.h"

namespace HardwareLayer
{
    class RotaryEncoder;
}

namespace PeripheralLayer
{
    class RotaryEventSource
        : public EventSource
    {
    public:
        RotaryEventSource(HardwareLayer::RotaryEncoder& encoder);

        virtual bool EventAvailable();
        virtual EventType Get();

    private:
        HardwareLayer::RotaryEncoder& m_Encoder;
    };
}
