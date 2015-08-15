#pragma once

#include "EventSource.h"

namespace PeripheralLayer
{
    class SerialEventSource
        : public EventSource
    {
    public:
        virtual bool EventAvailable();
        virtual EventType Get();
    };
}
