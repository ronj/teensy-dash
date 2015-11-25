#pragma once

#include "Math.h"

#include <cmath>

namespace Common
{
    namespace Interpolation
    {
        template <typename T>
        T Linear(T a, T b, float t)
        {
            return static_cast<T>(a * (1 - t) + b * t);
        }

		template <typename T>
		T Cosine(T a, T b, float t)
		{
			double tt;

			tt = (1 - std::cos(t * Math::PI<T>)) / 2;
			return static_cast<T>(a * (1 - tt) + b * tt);
		}
    }
}
