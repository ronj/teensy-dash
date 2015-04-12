#include "Math.h"

#ifdef BUILD_FOR_EMULATOR
	int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
	{
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
#else
    #include "WProgram.h"
#endif

int32_t Common::Math::Map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
{
	return map(x, in_min, in_max, out_min, out_max);
}
