#include "TeensyAnalogPin.h"

#include "Common/ArduinoWrapper.h"

HardwareLayer::TeensyAnalogPin::TeensyAnalogPin(const uint8_t pin)
	: m_Pin(pin)
{
}

uint16_t HardwareLayer::TeensyAnalogPin::Read() const
{
	return analogRead(m_Pin);
}

void HardwareLayer::TeensyAnalogPin::Write(uint16_t value)
{
	analogWrite(m_Pin, value);
}
