#include "yaffut.h"

#include "Common/Logger.h"

#include <iostream>
#include <sstream>
#include <regex>

struct LoggerTest
{
	LoggerTest()
	    : previous(std::cout.rdbuf())
	{
		// Redirect streaming to std::cout to our own buffer.
		std::cout.rdbuf(actual.rdbuf());
	}

	~LoggerTest()
	{
		ResetActual();
		std::cout.rdbuf(previous);
	}

	void ResetActual()
	{
		actual.str("");
		actual.clear();
	}

	std::streambuf* previous;
	std::stringstream actual;
};

static const char* entry_func_name;
static unsigned int entry_func_line;
void test_entry_logger()
{
	LOG_METHOD_ENTRY;
	entry_func_line = __LINE__ - 1;
	entry_func_name = __PRETTY_FUNCTION__;
}

static const char* exit_func_name;
static unsigned int exit_func_line;
void test_exit_logger()
{
	LOG_METHOD_EXIT;
	exit_func_line = __LINE__ - 1;
	exit_func_name = __PRETTY_FUNCTION__;
}

TEST(LoggerTest, should_log_simple_string_message)
{
	Common::Logger::Get().Log("Hello Logger!");
	EXPECT_EQ("Hello Logger!", actual.str());
}

TEST(LoggerTest, should_log_message_with_newline)
{
	Common::Logger::Get().LogLine("Including Newline");
	EXPECT_EQ("Including Newline\n", actual.str());
}

TEST(LoggerTest, should_log_pod_types)
{
	Common::Logger::Get().Log(42);
	Common::Logger::Get().Log(',');
	Common::Logger::Get().Log(3.14159);

	EXPECT_EQ("42,3.14159", actual.str());
}

TEST(LoggerTest, should_log_variable_argument_list)
{
	Common::Logger::Get().Log('H', 'e', 'l', 'l', 'o', 123, 456.7f);

	EXPECT_EQ("Hello123456.7", actual.str());
}

TEST(LoggerTest, should_log_expectation)
{
	Common::Logger::Get().LogExpectation("value:9001");
	EXPECT_EQ("?:value:9001\n", actual.str());
}

TEST(LoggerTest, should_log_broken_contract)
{
	Common::Logger::Get().LogBrokenContract("0 == 1");
	EXPECT_EQ("Assertion failed: 0 == 1\n", actual.str());
}

TEST(LoggerTest, should_log_method_entry)
{
	std::regex re("test_Logger.cpp(.*)");
	std::smatch match;

	test_entry_logger();

	std::string result = actual.str();

	EXPECT_TRUE(std::regex_search(result, match, re));
	//EXPECT_EQ("test_Logger.cpp(" + std::to_string(entry_func_line) + ") [" + std::string(entry_func_name) + "] Entry", match[0].str());
}

TEST(LoggerTest, should_log_method_exit)
{
	std::regex re("test_Logger.cpp(.*)");
	std::smatch match;

	test_exit_logger();

	std::string result = actual.str();

	EXPECT_TRUE(std::regex_search(result, match, re));
	//EXPECT_EQ("test_Logger.cpp(" + std::to_string(exit_func_line) + ") [" + std::string(exit_func_name) + "] Exit", match[0].str());
}
