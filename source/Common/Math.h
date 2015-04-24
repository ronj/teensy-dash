#pragma once

#include "Config.h"

#include <cinttypes>

namespace Common
{
    namespace Math
    {
		CFG_CONSTEXPR float PI = 3.141592653589793238462643383279502884e+00f;

        int32_t Map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max);

        template <typename T>
		T Sign(T value)
		{ 
			return (value > 0) - (value < 0); 
		}
    }
}
