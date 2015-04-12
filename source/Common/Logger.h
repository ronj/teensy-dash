#pragma once

#include "NonCopyable.h"

#include "WProgram.h"

#undef min
#undef max
#undef swap
#undef PI

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
			Serial.println(toLog);
		}

	private:
		Logger()
		{
			Serial.begin(9600);
		}
	};
}
