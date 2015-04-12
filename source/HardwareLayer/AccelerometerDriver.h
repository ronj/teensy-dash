#pragma once

#include <cinttypes>

namespace HardwareLayer
{
	class AccelerometerDriver
	{
	public:
		virtual int32_t GetXAcceleration() const = 0;
		virtual int32_t GetYAcceleration() const = 0;
		virtual int32_t GetZAcceleration() const = 0;
	};
}
