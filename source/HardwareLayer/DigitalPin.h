#pragma once

#include "Common/NonCopyable.h"

#include <functional>

namespace HardwareLayer
{
	enum class PinType { Input, Output, InputPullUp };
    enum class InterruptType { Rising, Falling, Change, Low, High };

	class DigitalPin
        : public Common::NonCopyable
	{
	public:
        virtual void EnableInterrupt(InterruptType mode, std::function<void()> isr) = 0;
	};
}
