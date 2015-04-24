#pragma once

#include "Hardware.h"

#include "ADXL335Driver.h"
#include "ST7735DisplayDriver.h"
#include "TeensyAnalogPin.h"
#include "TeensyDigitalPin.h"
#include "TeensyPlatform.h"
#include "TeensyRotaryEncoder.h"
#include "TeensyTimer.h"

namespace HardwareLayer
{
	class TeensyHardware : public Hardware
	{
	public:
		TeensyHardware();

		virtual AccelerometerDriver& GetAccelerometerDriver();
		virtual DisplayDriver& GetDisplayDriver();
		virtual Timer& GetTimer();
		virtual RotaryEncoder& GetRotaryEncoder();
		virtual DigitalPin& GetVSSPin();

	private:
		TeensyPlatform m_Platform;

		const TeensyAnalogPin m_XPin;
		const TeensyAnalogPin m_YPin;
		const TeensyAnalogPin m_ZPin;

		TeensyDigitalPin m_VSSPin;

		TeensyTimer m_Timer;
		ADXL335Driver m_AccelerometerDriver;
		ST7735DisplayDriver m_DisplayDriver;
		TeensyRotaryEncoder m_RotaryEncoder;
	};
}
