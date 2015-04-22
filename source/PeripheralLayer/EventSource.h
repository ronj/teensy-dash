#pragma once

#include "EventTypes.h"

#include "Common/List.h"

namespace PeripheralLayer
{
    class EventSource
        : public Common::List<EventSource>::Element
    {
    public:
        virtual bool EventAvailable() = 0;
        virtual EventType Get() = 0;

    protected:
        EventSource();
    };
}
