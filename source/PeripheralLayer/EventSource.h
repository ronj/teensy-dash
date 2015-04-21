#pragma once

#include <cinttypes>

#include "EventTypes.h"

#include "Common/NonCopyable.h"

namespace PeripheralLayer
{
    class EventSource
        : public Common::NonCopyable
    {
    public:
        virtual bool EventAvailable() const = 0;
        virtual EventType Get() = 0;
    };
}
