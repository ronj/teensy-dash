#include "TeensyDigitalPin.h"

#include "Common/ArduinoWrapper.h"

namespace
{
    static HardwareLayer::TeensyDigitalPin* self = nullptr;

    void ISR()
    {
    	if (self)
    	{
        	self->OnInterrupt();
        }
    }
}

HardwareLayer::TeensyDigitalPin::TeensyDigitalPin(const uint8_t pin)
    : m_Pin(pin)
{
	self = this;
    pinMode(m_Pin, INPUT);
}

void HardwareLayer::TeensyDigitalPin::EnableInterrupt(InterruptType edge)
{
    attachInterrupt(m_Pin, ISR, RISING);
}
