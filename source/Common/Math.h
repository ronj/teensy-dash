#pragma once

#include <cinttypes>

namespace Common
{
    namespace Math
    {
        constexpr float PI = 3.141592653589793238462643383279502884e+00;
        int32_t Map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max);
    }
}
