#pragma once

#include "Hardware.h"

#include "TeensyAnalogPin.h"
#include "ADXL335Driver.h"
#include "ST7735DisplayDriver.h"
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

	private:
		const TeensyAnalogPin m_XPin;
		const TeensyAnalogPin m_YPin;
		const TeensyAnalogPin m_ZPin;

		TeensyTimer m_Timer;
		ADXL335Driver m_AccelerometerDriver;
		ST7735DisplayDriver m_DisplayDriver;
	};
}
