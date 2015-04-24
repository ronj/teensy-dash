#pragma once

#include "Common/NonCopyable.h"

#include <functional>

namespace HardwareLayer
{
    enum class InterruptType { Rising, Falling, Change };

	class DigitalPin
        : public Common::NonCopyable
	{
	public:
        virtual void EnableInterrupt(InterruptType edge) = 0;
		std::function<void()> OnInterrupt;
	};
}
