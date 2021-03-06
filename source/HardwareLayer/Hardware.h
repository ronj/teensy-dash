#pragma once

namespace HardwareLayer
{
	class AccelerometerDriver;
	class AnalogPin;
	class DigitalPin;
	class DisplayDriver;
	class FrequencyCounter;
	class LedDriver;
	class Platform;
	class RotaryEncoder;
	class Timer;

	class Hardware
	{
	public:
		virtual Platform& GetPlatform() = 0;
		virtual AccelerometerDriver& GetAccelerometerDriver() = 0;
		virtual DisplayDriver& GetDisplayDriver() = 0;
		virtual LedDriver& GetLedDriver() = 0;
		virtual Timer& GetTimer() = 0;
		virtual RotaryEncoder& GetRotaryEncoder() = 0;
		virtual DigitalPin& GetVSSPin() = 0;
		virtual DigitalPin& GetInjectorPin() = 0;
		virtual DigitalPin& GetParkingSensorPin() = 0;
		virtual DigitalPin& GetButtonPin() = 0;
		virtual FrequencyCounter& GetRPMFrequencyCounter() = 0;
		virtual const AnalogPin& GetBatteryVoltagePin() = 0;
		virtual AnalogPin& GetBacklightPin() = 0;
	};
}
