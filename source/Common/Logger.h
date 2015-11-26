#pragma once

#include "DashCompilerDetection.h"

#ifdef BUILD_FOR_EMULATOR
	#include <iostream>
#else
	#include "Common/ArduinoWrapper.h"
#endif

#include <cassert>

namespace Common
{
	class Logger
	{
	public:
		Logger(const Logger&) CFG_DELETED_FUNCTION;
		Logger& operator=(const Logger&) CFG_DELETED_FUNCTION;

		static Logger& Get()
		{
			static Logger instance;
			return instance;
		}

		template <typename T>
		void DoLog(const T& toLog) const
		{
#ifdef BUILD_FOR_EMULATOR
			std::cout << toLog;
#else
			Serial.print(toLog);
#endif
		}

		template <typename T, typename... Args>
		void DoLog(const T& toLog, Args... args) const
		{
#ifdef BUILD_FOR_EMULATOR
			std::cout << toLog;
#else
			Serial.print(toLog);
#endif
			DoLog(args...);
		}

		template <typename... Args>
		void Log(Args... args) const
		{
			DoLog(args...);
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
			Log("?:");
			LogLine(toLog);
		}

		template <typename T>
		void LogBrokenContract(const T& toLog) const
		{
			Log("Assertion failed: ");
			LogLine(toLog);
		}

	private:
		Logger() = default;
	};

	class LogDecorator
	{
	public:
		LogDecorator(const char* file, unsigned int line, const char* function)
			: m_File(file)
			, m_Line(line)
			, m_Function(function)
		{
			Common::Logger& logger = Logger::Get();

			logger.Log(m_File, '(', m_Line, ") [", m_Function, "] ");
		}

		Common::Logger& GetLogger() { return Logger::Get(); }

	private:
		const char* m_File;
		unsigned int m_Line;
		const char* m_Function;
	};
}

#if !(defined(__PRETTY_FUNCTION__))
#define __PRETTY_FUNCTION__ __FUNCTION__
#endif

#define INTERNAL_FILE_LINE_DECORATOR Common::LogDecorator(__FILE__, __LINE__, __PRETTY_FUNCTION__).GetLogger()

#define LOG_METHOD_ENTRY INTERNAL_FILE_LINE_DECORATOR.LogLine("Entry");
#define LOG_METHOD_EXIT  INTERNAL_FILE_LINE_DECORATOR.LogLine("Exit");

#define ASSERT_THAT(boolean_expression) \
	if (false == (boolean_expression)) \
	{ \
		INTERNAL_FILE_LINE_DECORATOR.LogBrokenContract(#boolean_expression); \
		assert(boolean_expression); \
	}
