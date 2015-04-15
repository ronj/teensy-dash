#pragma once

#include "NonCopyable.h"

#ifdef BUILD_FOR_EMULATOR
	#include <iostream>
#else
	#include "WProgram.h"
	#undef min
	#undef max
	#undef abs
	#undef PI
#endif

namespace Common
{
	class Logger : public NonCopyable
	{
	public:
		static Logger& Get()
		{
			static Logger instance;
			return instance;
		}

		template <typename T>
		void Log(const T& toLog) const
		{
#ifdef BUILD_FOR_EMULATOR
			std::cout << toLog << std::endl;
#else
			Serial.println(toLog);
#endif
		}

	private:
		Logger()
		{
#ifndef BUILD_FOR_EMULATOR
			Serial.begin(9600);
#endif
		}
	};
}
