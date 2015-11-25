#pragma once

#include "DashCompilerDetection.h"

#include <cinttypes>

namespace Common
{
    namespace Math
    {
#if CFG_COMPILER_CXX_CONSTEXPR
		template <class T>
		CFG_CONSTEXPR T PI = static_cast<T>(3.141592653589793238462643383279502884);
#else
		static const float PI = 3.141592653589793238462643383279502884e+00f;
#endif

        int32_t Map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max);

		template <typename T>
		CFG_CONSTEXPR T Sign(T value)
		{ 
			return (value > 0) - (value < 0); 
		}
    }
}
