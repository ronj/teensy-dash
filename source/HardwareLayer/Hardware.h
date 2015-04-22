#pragma once

namespace HardwareLayer
{
	class AccelerometerDriver;
	class DisplayDriver;
	class RotaryEncoder;
	class Timer;

	class Hardware
	{
	public:
		virtual AccelerometerDriver& GetAccelerometerDriver() = 0;
		virtual DisplayDriver& GetDisplayDriver() = 0;
		virtual Timer& GetTimer() = 0;
		virtual RotaryEncoder& GetRotaryEncoder() = 0;
	};
}
