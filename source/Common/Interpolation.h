#pragma once

#include "Common/Math.h"

#include <cmath>

namespace Common
{
    namespace Interpolation
    {
        template <typename T>
        T Linear(T a, T b, float t)
        {
            return a * (1 - t) + b * t;
        }

		template <typename T>
		T Cosine(T a, T b, float t)
		{
			double tt;

			tt = (1 - std::cos(t * Math::PI)) / 2;
			return a * (1 - tt) + b * tt;
		}
    }
}
