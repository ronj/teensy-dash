#pragma once

#include "Hardware.h"

#include "ADXL335Driver.h"
#include "SDLAnalogPin.h"
#include "SDLDisplayDriver.h"
#include "SDLPlatform.h"
#include "SDLRotaryEncoder.h"
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
		virtual RotaryEncoder& GetRotaryEncoder();

	private:
		SDLPlatform m_Platform;

		SDLAnalogPin m_X;
		SDLAnalogPin m_Y;
		SDLAnalogPin m_Z;

		SDLTimer m_Timer;
		ADXL335Driver m_AccelerometerDriver;
		SDLDisplayDriver m_DisplayDriver;
		SDLRotaryEncoder m_RotaryEncoder;
	};
}
