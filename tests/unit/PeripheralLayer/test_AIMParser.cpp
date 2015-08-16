#include "yaffut.h"

#include "Common/Logger.h"

#include <array>
#include <cinttypes>

enum class AIMSignal
{
	RPM,
	WheelSpeed,
	OilPressure,
	Unknown
};

class AIMParser
{
public:
	AIMParser()
		: m_SignalValues({ { 0 } })
	{
	}

	virtual bool Parse(const uint8_t* buffer, uint32_t length) = 0;

	uint16_t GetRawSignalValue(AIMSignal signal) const
	{
		ASSERT_THAT(signal < AIMSignal::Unknown);
		return m_SignalValues[static_cast<uint8_t>(signal)];
	}

protected:
	virtual AIMSignal ChannelToSignal(uint8_t channel) const
	{
		switch (channel)
		{
		case 1: return AIMSignal::RPM;
		case 5: return AIMSignal::WheelSpeed;
		case 9: return AIMSignal::OilPressure;
		}

		return AIMSignal::Unknown;
	}

	bool ValidateChecksum(const uint8_t* buffer, uint32_t length, uint8_t expected) const
	{
		uint8_t sum = 0;
		for (uint8_t i = 0; i < length; ++i)
		{
			sum += buffer[i];
		}

		return sum == expected;
	}

protected:
	static const uint8_t MAX_AIM_SIGNALS = 15;
	std::array<uint16_t, MAX_AIM_SIGNALS> m_SignalValues;
};

class SerialAIMParser : public AIMParser
{
public:
	virtual bool Parse(const uint8_t* buffer, uint32_t length)
	{
		ASSERT_THAT(length == 5);

		if ((buffer[MARKER_BYTE] == AIM_SERIAL_MARKER) &&
			ValidateChecksum(buffer, 4, buffer[CHECKSUM_BYTE]))
		{
			uint8_t signal = static_cast<uint8_t>(ChannelToSignal(buffer[CHANNEL_BYTE]));
			if (signal < MAX_AIM_SIGNALS)
			{
				m_SignalValues[signal] = buffer[HIGH_DATA_BYTE] << 8 | buffer[LOW_DATA_BYTE];
				return true;
			}
		}

		return false;
	}

private:
	static const uint8_t CHANNEL_BYTE = 0;
	static const uint8_t MARKER_BYTE = 1;
	static const uint8_t HIGH_DATA_BYTE = 2;
	static const uint8_t LOW_DATA_BYTE = 3;
	static const uint8_t CHECKSUM_BYTE = 4;

	static const uint8_t AIM_SERIAL_MARKER = 0xA3;
};

struct AIMParserTest
{
	void AssertInvalidParseResult(const std::array<uint8_t, 5>& message, AIMSignal signal)
	{
		SerialAIMParser parser;
		EQUAL(false, parser.Parse(message.data(), message.size()));
		EQUAL(0, parser.GetRawSignalValue(signal));
	}
};

TEST(AIMParserTest, should_have_correct_initial_values)
{
	SerialAIMParser parser;

	EQUAL(0, parser.GetRawSignalValue(AIMSignal::RPM));
	EQUAL(0, parser.GetRawSignalValue(AIMSignal::WheelSpeed));
	EQUAL(0, parser.GetRawSignalValue(AIMSignal::OilPressure));
}

TEST(AIMParserTest, should_parse_properly_aligned_aim_message)
{
	std::array<uint8_t, 5> message = { 0x01, 0xA3, 0x03, 0xE8, 0x8F };

	SerialAIMParser parser;

	CHECK(parser.Parse(message.data(), message.size()));
	EQUAL(1000, parser.GetRawSignalValue(AIMSignal::RPM));
}

TEST(AIMParserTest, should_ignore_aim_message_with_invalid_checksum)
{
	AssertInvalidParseResult({ { 0x01, 0xA3, 0x03, 0xE8, 0xFF } }, AIMSignal::RPM);
}

TEST(AIMParserTest, should_ignore_aim_message_with_invalid_marker)
{
	AssertInvalidParseResult({ { 0x01, 0xAA, 0x03, 0xE8, 0x8F } }, AIMSignal::RPM);
}

TEST(AIMParserTest, should_ignore_aim_message_with_invalid_channel)
{
	AssertInvalidParseResult({ { 0xFF, 0xA3, 0x03, 0xE8, 0x8F } }, AIMSignal::RPM);
}

TEST(AIMParserTest, should_parse_all_known_aim_channels)
{

}
