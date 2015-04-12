#pragma once

#include "NonCopyable.h"

#include "WProgram.h"

#undef min
#undef max
#undef swap

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
		void Log(T& toLog)
		{
			Serial.println(toLog);
		}

	private:
		Logger()
		{
			Serial.begin(9600);
		}
	};
}
