#include "SpeedModel.h"

#include "ConversionHelper.h"

#include "WProgram.h"

static volatile unsigned long counter = 0;

void isrCounter()
{
	++counter;
}

ApplicationLayer::Models::SpeedModel::SpeedModel()
	: m_Speed(0)
{
	pinMode(23, INPUT); // sets the digital pin as output
	attachInterrupt(23, isrCounter, RISING); // interrrupt 1 is data ready
}

int32_t ApplicationLayer::Models::SpeedModel::GetRawValue() const
{
	return m_Speed;
}

const char* ApplicationLayer::Models::SpeedModel::GetFormattedValue() const
{
	static char formatted[4] = { 0 };
	itoa2(GetRawValue() / 10, formatted, 10);
	return formatted;
}

void ApplicationLayer::Models::SpeedModel::Update(uint32_t now)
{
	static unsigned long previous = 0;

	if (now - previous > 1000)
	{
		m_Speed = ConvertPulsesToSpeed(counter, now - previous);
		previous = now;
		cli();
		counter = 0;
		sei();
	}
}

int32_t ApplicationLayer::Models::SpeedModel::ConvertPulsesToSpeed(int32_t pulses, int32_t timediff) const
{
	return static_cast<int32_t>((pulses / (PulsesPerKM / (3.6f * timediff))) * 10);
}
