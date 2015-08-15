#include "SDLFrequencyCounter.h"

bool HardwareLayer::SDLFrequencyCounter::Available()
{
	return true;
}

uint32_t HardwareLayer::SDLFrequencyCounter::Read()
{
	return 0;
}

float HardwareLayer::SDLFrequencyCounter::CountToFrequency(uint32_t count)
{
	return 60.f;
}
