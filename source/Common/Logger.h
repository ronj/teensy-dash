#pragma once

#include "NonCopyable.h"

#ifdef BUILD_FOR_EMULATOR
	#include <iostream>
#else
	#include "Common/ArduinoWrapper.h"
#endif

#if !(defined(__PRETTY_FUNCTION__))
	#define __PRETTY_FUNCTION__   __FUNCTION__
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
			std::cout << toLog;
#else
			Serial.print(toLog);
#endif
		}

		template <typename T>
		void LogLine(const T& toLog) const
		{
#ifdef BUILD_FOR_EMULATOR
			std::cout << toLog << std::endl;
#else
			Serial.println(toLog);
#endif
		}

		template <typename T>
		void LogExpectation(const T& toLog) const
		{
			LogLine(toLog);
		}

	private:
		Logger() CFG_DECL_DEFAULT;
	};

	class LogHelper
	{
	public:
		LogHelper(const char* file, unsigned int line, const char* function)
			: m_File(file)
			, m_Line(line)
			, m_Function(function)
		{
		}

		template <typename T>
		void Debug(const T& toLog)
		{
			Logger::Get().Log(m_File);
			Logger::Get().Log('@');
			Logger::Get().Log(m_Line);
			Logger::Get().Log(" [");
			Logger::Get().Log(m_Function);
			Logger::Get().Log("]: ");
			Logger::Get().LogLine(toLog);
		}

	private:
		const char* m_File;
		unsigned int m_Line;
		const char* m_Function;
	};

#define LOG LogHelper(__FILE__, __LINE__, __PRETTY_FUNCTION__)
}
