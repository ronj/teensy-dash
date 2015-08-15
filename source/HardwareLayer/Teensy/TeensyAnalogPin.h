#pragma once

#include "AnalogPin.h"

namespace HardwareLayer
{
	class TeensyAnalogPin
		: public AnalogPin
	{
	public:
		TeensyAnalogPin(const uint8_t pin);

		virtual uint16_t Read() const;
		virtual void Write(uint16_t value);

	private:
		const uint8_t m_Pin;
	};
}
