#pragma once

#include "Hardware.h"

#include "SDLAnalogPin.h"
#include "ADXL335Driver.h"
#include "SDLDisplayDriver.h"
#include "SDLTimer.h"

namespace HardwareLayer
{
	class SDLHardware : public Hardware
	{
	public:
		SDLHardware();

		virtual AccelerometerDriver& GetAccelerometerDriver();
		virtual DisplayDriver& GetDisplayDriver();
		virtual Timer& GetTimer();

	private:
		SDLAnalogPin m_X;
		SDLAnalogPin m_Y;
		SDLAnalogPin m_Z;

		SDLTimer m_Timer;
		ADXL335Driver m_AccelerometerDriver;
		SDLDisplayDriver m_DisplayDriver;
	};
}
