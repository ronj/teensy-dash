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
}
