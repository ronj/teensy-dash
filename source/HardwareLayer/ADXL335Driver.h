#pragma once

#include "AccelerometerDriver.h"

namespace HardwareLayer
{
	class AnalogPin;
	class Timer;

	class ADXL335Driver : public AccelerometerDriver
	{
	public:
		ADXL335Driver(const AnalogPin& xPin, const AnalogPin& yPin, const AnalogPin& zPin, const Timer& timer);

		virtual int32_t GetXAcceleration() const;
		virtual int32_t GetYAcceleration() const;
		virtual int32_t GetZAcceleration() const;

	private:
		int32_t ReadAxis(const AnalogPin& pin) const;

	private:
		const uint8_t m_SampleSize = 10;

		const Timer& m_Timer;

		const AnalogPin& m_XPin;
		const AnalogPin& m_YPin;
		const AnalogPin& m_ZPin;
	};
}
