#pragma once

#include "NonCopyable.h"

#ifdef BUILD_FOR_EMULATOR
	#include <iostream>
#else
	#include "Common/ArduinoWrapper.h"
#endif

#include <cassert>

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

		template <typename T>
		void LogBrokenContract(const T& toLog) const
		{
			Log("Assertion failed: ");
			LogLine(toLog);

			assert(false);
		}

	private:
		Logger() CFG_DECL_DEFAULT;
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

			logger.Log(m_File);
			logger.Log('(');
			logger.Log(m_Line);
			logger.Log(") [");
			logger.Log(m_Function);
			logger.Log("] ");
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

#define LOG_METHOD_ENTRY INTERNAL_FILE_LINE_DECORATOR.Log('\n');

#define CHECK_IF(boolean_expression) \
	if (false == (boolean_expression)) INTERNAL_FILE_LINE_DECORATOR.LogBrokenContract(#boolean_expression)
