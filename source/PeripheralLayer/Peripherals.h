#pragma once

#include "AccelerationAxis.h"
#include "Configuration.h"
#include "GraphicContext.h"
#include "PulseCounter.h"
#include "RotaryEventSource.h"
#include "SerialEventSource.h"
#include "TimeProvider.h"
#include "VoltageDivider.h"
#include "Voltmeter.h"

namespace HardwareLayer
{
	class Hardware;
}

namespace PeripheralLayer
{
	class Peripherals
	{
	public:
		Peripherals(HardwareLayer::Hardware& hardware);

		const Configuration& GetConfiguration() const;

		GraphicContext& GetGraphicContext();
		TimeProvider& GetTimeProvider();

		AccelerationAxis& GetXAcceleration();
		AccelerationAxis& GetYAcceleration();
		AccelerationAxis& GetZAcceleration();

		PulseCounter& GetVSSPulseCounter();
		PulseCounter& GetRPMPulseCounter();

		RotaryEventSource& GetRotaryEventSource();
		SerialEventSource& GetSerialEventSource();

		Voltmeter& GetBatteryVoltageMeter();

	private:
		Configuration m_Configuration;

		GraphicContext m_GraphicContext;
		TimeProvider m_TimeProvider;

		AccelerationAxis m_XAccelerationAxis;
		AccelerationAxis m_YAccelerationAxis;
		AccelerationAxis m_ZAccelerationAxis;

		PulseCounter m_VSSPulseCounter;
		PulseCounter m_RPMPulseCounter;

		RotaryEventSource m_RotaryEventSource;
		SerialEventSource m_SerialEventSource;

		VoltageDivider m_BatteryVoltageDivider;
		Voltmeter m_BatteryVoltageMeter;
	};
}
