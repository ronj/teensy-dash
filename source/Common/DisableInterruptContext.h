#pragma once

#ifndef BUILD_FOR_EMULATOR
	#include "Common/ArduinoWrapper.h"
#endif

namespace Common
{
    class DisableInterruptContext
    {
	public:
		DisableInterruptContext()
		{
#ifndef BUILD_FOR_EMULATOR
			cli();
#endif
		}

		~DisableInterruptContext()
		{
#ifndef BUILD_FOR_EMULATOR
			sei();
#endif
		}
    };

	namespace Atomic
	{
		template <typename T>
		T CopyAndResetValue(T& t)
		{
			T val = 0;
			{
				Common::DisableInterruptContext disableInterrupts;
				val = t;
				t = 0;
			}

			return val;
		}
	}
}
