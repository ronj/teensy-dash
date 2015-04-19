#pragma once

#ifndef BUILD_FOR_EMULATOR
	#include "Arduino.h"
	#undef min
	#undef max
	#undef abs
	#undef swap
	#undef PI
#endif
