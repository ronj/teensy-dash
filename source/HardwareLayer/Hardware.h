#pragma once

namespace HardwareLayer
{
	class AccelerometerDriver;
	class AnalogPin;
	class DigitalPin;
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
		virtual DigitalPin& GetVSSPin() = 0;
		virtual DigitalPin& GetRPMPin() = 0;
		virtual const AnalogPin& GetBatteryVoltagePin() = 0;
	};
}
