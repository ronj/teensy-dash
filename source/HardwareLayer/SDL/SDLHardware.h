#pragma once

#include "Hardware.h"

#include "ADXL335Driver.h"
#include "SDLAnalogPin.h"
#include "SDLDigitalPin.h"
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

		virtual Platform& GetPlatform();
		virtual AccelerometerDriver& GetAccelerometerDriver();
		virtual DisplayDriver& GetDisplayDriver();
		virtual Timer& GetTimer();
		virtual RotaryEncoder& GetRotaryEncoder();
		virtual DigitalPin& GetVSSPin();
		virtual DigitalPin& GetRPMPin();
		virtual const AnalogPin& GetBatteryVoltagePin();

	private:
		SDLPlatform m_Platform;

		SDLAnalogPin m_X;
		SDLAnalogPin m_Y;
		SDLAnalogPin m_Z;

		const SDLAnalogPin m_BatteryVoltagePin;

		SDLDigitalPin m_VSSPin;
		SDLDigitalPin m_RPMPin;

		SDLTimer m_Timer;
		ADXL335Driver m_AccelerometerDriver;
		SDLDisplayDriver m_DisplayDriver;
		SDLRotaryEncoder m_RotaryEncoder;
	};
}
