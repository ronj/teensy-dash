#include "ParkDistanceDecoder.h"

#include "Common/DisableInterruptContext.h"
#include "Common/Logger.h"

#include "HardwareLayer/DigitalPin.h"

#include "PeripheralLayer/TimeProvider.h"

#include <limits>

/* The protocol for cheap parking sensor units is typically as follows:

   Values are encoded in a pulse width modulated bit-stream.
   A logic one has a certain length and a logic zero another length.

   These bits form messages, which contain the measurement for a
   single sensor.

   Messages are prepended with a start bit of 1000 µS, a logic '0'
   has a length of 85 µS and a logic '1' has a length of 225 µS.
   At the end of a message is a stop bit, which has the same
   characteristics as a logic '0'.

   So for my specific kit a message has the form:

   --------------------------------------------
   | START_BIT | ADDRESS |   VALUE | STOP_BIT |
   --------------------------------------------

   Where ADDRESS is 8 bits and value is 8 bits, making for a 16 bit
   payload length.

   The high nibble of ADDRESS is always 0b1000. The low nibble
   contains the sensor address (0, 1, 2, 3) and the most significant
   bit indicates if the sensor is currently reading a value. In case
   this bit is set the sensor could be not connected, reading a distance
   of more than or equal to 250 cm or the sensor could be broken.

   VALUE contains the measured value in centimeters. Making the range
   from 254 to 0 cm in 1 cm increments.
*/

namespace
{
	volatile uint32_t risingEdgeStartTime = 0;
	volatile uint16_t scratchpad = 0;
	volatile uint8_t bitsFound = 0;

	const uint8_t MESSAGE_LENGTH = 16; // Messages are 16 bits long
	const uint8_t SENSOR_PREAMBLE = 0x80; // (0b1000 0000)
	const uint8_t SENSOR_ADDRESS_MASK = 0xF7; // (0b1111 0111)

	const uint8_t SENSOR_A_ADDRESS = SENSOR_PREAMBLE + 0;
	const uint8_t SENSOR_B_ADDRESS = SENSOR_PREAMBLE + 1;
	const uint8_t SENSOR_C_ADDRESS = SENSOR_PREAMBLE + 2;
	const uint8_t SENSOR_D_ADDRESS = SENSOR_PREAMBLE + 3;
}

template <uint8_t bit, typename T>
void set_bit(T& x)
{
	static_assert(std::is_unsigned<T>::value, "T should be unsigned");
	x |= static_cast<uintmax_t>(1) << bit;
}

template <uint8_t bit, typename T>
void clear_bit(T& x)
{
	static_assert(std::is_unsigned<T>::value, "T should be unsigned");
	x &= ~(static_cast<uintmax_t>(1) << bit);
}

template <uint8_t bit, typename T>
void toggle_bit(T& x)
{
	static_assert(std::is_unsigned<T>::value, "T should be unsigned");
	x ^= static_cast<uintmax_t>(1) << bit;
}

template <uint8_t bit, typename T>
bool check_bit(T x)
{
	static_assert(std::is_unsigned<T>::value, "T should be unsigned");
	return (x >> bit) & static_cast<uintmax_t>(1);
}

PeripheralLayer::ParkDistanceDecoder::ParkDistanceDecoder(HardwareLayer::DigitalPin& pin, PeripheralLayer::TimeProvider& time)
	: m_Pin(pin)
	, m_Time(time)
{
	m_Pin.OnInterrupt = [this]() { Decode(); };
	m_Pin.EnableInterrupt(HardwareLayer::InterruptType::Change);
}

uint32_t PeripheralLayer::ParkDistanceDecoder::GetPackedDistances() const
{
	uint32_t packedDistances = 0;
	{
		Common::DisableInterruptContext disableInterrupts;
		packedDistances = m_PackedDistances;
	}

	return packedDistances;
}

void PeripheralLayer::ParkDistanceDecoder::Decode()
{
	if (m_Pin.Read() == 1)
	{
		risingEdgeStartTime = m_Time.TickCountMicroseconds();
	}
	else
	{
		uint32_t duration = m_Time.TickCountMicroseconds() - risingEdgeStartTime;

		if (duration > 200 && duration < 250)
		{
			set_bit<0>(scratchpad);
			bitsFound++;
			scratchpad <<= 1;
		}
		else if (duration > 80 && duration < 100 && bitsFound < MESSAGE_LENGTH - 1)
		{
			clear_bit<0>(scratchpad);
			bitsFound++;
			scratchpad <<= 1;
		}
		else
		{
			// Start bit or stop bit found.
			scratchpad = 0;
			bitsFound = 0;
		}
	}

	if (bitsFound == MESSAGE_LENGTH - 1)
	{
		uint8_t address = (scratchpad >> 8) & 0xFF;
		uint8_t value = scratchpad & 0xFF;

		if (check_bit<3>(address))
		{
			value = std::numeric_limits<uint8_t>::max();
		}

		switch (address & SENSOR_ADDRESS_MASK)
		{
		case SENSOR_A_ADDRESS:
			m_PackedDistances &= ~(0xFF000000);
			m_PackedDistances |= (static_cast<uint32_t>(value) << 24) & 0xFF000000;
			break;
		case SENSOR_B_ADDRESS:
			m_PackedDistances &= ~(0x00FF0000);
			m_PackedDistances |= (static_cast<uint32_t>(value) << 16) & 0x00FF0000;
			break;
		case SENSOR_C_ADDRESS:
			m_PackedDistances &= ~(0x0000FF00);
			m_PackedDistances |= (static_cast<uint32_t>(value) << 8) & 0x0000FF00;
			break;
		case SENSOR_D_ADDRESS:
			m_PackedDistances &= ~(0x000000FF);
			m_PackedDistances |= value;
			break;
		}
	}
}
