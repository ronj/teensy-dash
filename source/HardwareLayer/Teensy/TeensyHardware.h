#pragma once

#include "Hardware.h"

#include "ADXL335Driver.h"
#include "NeoPixelLedDriver.h"
#include "ST7735DisplayDriver.h"
#include "TeensyAnalogPin.h"
#include "TeensyDigitalPin.h"
#include "TeensyFrequencyCounter.h"
#include "TeensyPlatform.h"
#include "TeensyRotaryEncoder.h"
#include "TeensyTimer.h"

namespace HardwareLayer
{
	class TeensyHardware : public Hardware
	{
	public:
		TeensyHardware();

		virtual Platform& GetPlatform();
		virtual AccelerometerDriver& GetAccelerometerDriver();
		virtual DisplayDriver& GetDisplayDriver();
		virtual LedDriver& GetLedDriver();
		virtual Timer& GetTimer();
		virtual RotaryEncoder& GetRotaryEncoder();
		virtual DigitalPin& GetVSSPin();
		virtual DigitalPin& GetInjectorPin();
		virtual DigitalPin& GetParkingSensorPin();
		virtual DigitalPin& GetButtonPin();
		virtual FrequencyCounter& GetRPMFrequencyCounter();
		virtual const AnalogPin& GetBatteryVoltagePin();
		virtual AnalogPin& GetBacklightPin();

	private:
		TeensyPlatform m_Platform;

		const TeensyAnalogPin m_XPin;
		const TeensyAnalogPin m_YPin;
		const TeensyAnalogPin m_ZPin;

		TeensyAnalogPin m_BacklightPin;
		const TeensyAnalogPin m_BatteryVoltagePin;

		TeensyDigitalPin m_VSSPin;
		TeensyDigitalPin m_InjectorPin;
		TeensyDigitalPin m_ParkingSensorPin;
		TeensyDigitalPin m_ButtonPin;
		TeensyFrequencyCounter m_RPMFrequencyCounter;

		TeensyTimer m_Timer;
		ADXL335Driver m_AccelerometerDriver;
		ST7735DisplayDriver m_DisplayDriver;
		NeoPixelLedDriver m_LedDriver;
		TeensyRotaryEncoder m_RotaryEncoder;
	};
}
