#pragma once

#include "Common/NonCopyable.h"

#include <cinttypes>
#include <functional>

namespace HardwareLayer
{
	enum class PinType { Input, Output, InputPullUp };
    enum class InterruptType { Rising, Falling, Change, Low, High };

	class DigitalPin
        : public Common::NonCopyable
	{
	public:
		virtual uint8_t Read() = 0;

        virtual void EnableInterrupt(InterruptType mode) = 0;
		virtual void DisableInterrupt() = 0;

		std::function<void()> OnInterrupt;
	};
}
