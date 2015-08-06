#include "ParkDistanceDecoder.h"

#include "Common/DisableInterruptContext.h"

#include "HardwareLayer/DigitalPin.h"

#include "PeripheralLayer/TimeProvider.h"

/* The protocol for cheap parking sensor units is typically as follows:

   Values are encoded in a pulse width modulated bit-stream.
   A logic one has a certain length and a logic zero another length.

   These bits form 24 bit messages, which contain the measurement for a
   single sensor. A message has the form:

   -------------------------------
   | ADDRESS |  ~VALUE |   VALUE |
   -------------------------------

   ADDRESS contains the sensor address as two nibbles, the first and second
   nibble are each others complement (e.g. 1111 0000).

   ~VALUE contains the complement of the measured value in centimeters.

   VALUE contains the measured value in centimeters.

   Because the address and value are stored and transmitted as complements
   it is possible to detect bit errors. If the two address nibbles are added
   the result should be all 1's (0xF). If the two values are added the results
   also should be all 1's (0xFF).

   The data stream itself repeats packages twice, so the actual stream looks like:
   AABBCCDDAABBCCDD...
*/

namespace
{
	volatile uint32_t risingEdgeStartTime = 0;
	volatile uint32_t scratchpad = 0;

	const uint8_t SENSOR_A_ADDRESS = 0xF0; // (0b1111 0000)
	const uint8_t SENSOR_B_ADDRESS = 0xD2; // (0b1101 0010)
	const uint8_t SENSOR_C_ADDRESS = 0xE1; // (0b1110 0001)
	const uint8_t SENSOR_D_ADDRESS = 0xC3; // (0b1100 0011)
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

		if (duration > 290 && duration < 310)
		{
			set_bit<0>(scratchpad);
		}
		else
		{
			clear_bit<0>(scratchpad);
		}

		scratchpad <<= 1;
	}

	uint8_t address = (scratchpad >> 16) & 0xFF;
	uint8_t valueComplement = (scratchpad >> 8) & 0xFF;
	uint8_t value = scratchpad & 0xFF;

	if (value + valueComplement == 0xFF)
	{
		switch (address)
		{
		case SENSOR_A_ADDRESS:
			m_PackedDistances |= (static_cast<uint32_t>(value) << 24) & 0xFF000000;
			break;
		case SENSOR_B_ADDRESS:
			m_PackedDistances |= (static_cast<uint32_t>(value) << 16) & 0x00FF0000;
			break;
		case SENSOR_C_ADDRESS:
			m_PackedDistances |= (static_cast<uint32_t>(value) << 8) & 0x0000FF00;
			break;
		case SENSOR_D_ADDRESS:
			m_PackedDistances |= value;
			break;
		}
	}
}
