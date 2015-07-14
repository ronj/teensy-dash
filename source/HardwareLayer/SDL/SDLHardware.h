#pragma once

#include "Hardware.h"

#include "ADXL335Driver.h"
#include "SDLAnalogPin.h"
#include "SDLDigitalPin.h"
#include "SDLDisplayDriver.h"
#include "SDLLedDriver.h"
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
		virtual DisplayDriver& GetLedDriver();
		virtual Timer& GetTimer();
		virtual RotaryEncoder& GetRotaryEncoder();
		virtual DigitalPin& GetVSSPin();
		virtual DigitalPin& GetRPMPin();
		virtual const AnalogPin& GetBatteryVoltagePin();
		virtual AnalogPin& GetBacklightPin();

	private:
		SDLPlatform m_Platform;

		SDLAnalogPin m_X;
		SDLAnalogPin m_Y;
		SDLAnalogPin m_Z;

		const SDLAnalogPin m_BatteryVoltagePin;
		SDLAnalogPin m_BacklightPin;

		SDLDigitalPin m_VSSPin;
		SDLDigitalPin m_RPMPin;

		SDLTimer m_Timer;
		ADXL335Driver m_AccelerometerDriver;
		SDLDisplayDriver m_DisplayDriver;
		SDLLedDriver m_LedDriver;
		SDLRotaryEncoder m_RotaryEncoder;
	};
}
