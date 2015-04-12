#include "ADXL335Driver.h"

#include "AnalogPin.h"
#include "Timer.h"

HardwareLayer::ADXL335Driver::ADXL335Driver(const AnalogPin& xPin, const AnalogPin& yPin, const AnalogPin& zPin, const Timer& timer)
	: m_Timer(timer)
	, m_XPin(xPin)
	, m_YPin(yPin)
	, m_ZPin(zPin)
{
}

int32_t HardwareLayer::ADXL335Driver::GetXAcceleration() const
{
	return ReadAxis(m_XPin);
}

int32_t HardwareLayer::ADXL335Driver::GetYAcceleration() const
{
	return ReadAxis(m_YPin);
}

int32_t HardwareLayer::ADXL335Driver::GetZAcceleration() const
{
	return ReadAxis(m_ZPin);
}

int32_t HardwareLayer::ADXL335Driver::ReadAxis(const AnalogPin& pin) const
{
	int32_t reading = 0;
	pin.Read();

	m_Timer.Sleep(1);

	for (int8_t i = 0; i < m_SampleSize; ++i)
	{
		reading += pin.Read();
	}

	return reading / m_SampleSize;
}
