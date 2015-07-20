#include "TeensyFrequencyCounter.h"

#include "FreqMeasure.h"

HardwareLayer::TeensyFrequencyCounter::TeensyFrequencyCounter()
{
	FreqMeasure.begin();
}

HardwareLayer::TeensyFrequencyCounter::~TeensyFrequencyCounter()
{
	FreqMeasure.end();
}

bool HardwareLayer::TeensyFrequencyCounter::Available()
{
	return FreqMeasure.available();
}

uint32_t HardwareLayer::TeensyFrequencyCounter::Read()
{
	return FreqMeasure.read();
}

float HardwareLayer::TeensyFrequencyCounter::CountToFrequency(uint32_t count)
{
	return FreqMeasure.countToFrequency(count);
}
