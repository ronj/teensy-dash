#pragma once

#include "AccelerationAxis.h"
#include "Configuration.h"
#include "FrequencyCounter.h"
#include "GraphicContext.h"
#include "ParkDistanceDecoder.h"
#include "PatternPlayer.h"
#include "PowerManagement.h"
#include "PulseCounter.h"
#include "PulseDuration.h"
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
		PowerManagement& GetPowerManagement();

		GraphicContext& GetGraphicContext();
		PatternPlayer& GetPatternPlayer();
		TimeProvider& GetTimeProvider();

		AccelerationAxis& GetXAcceleration();
		AccelerationAxis& GetYAcceleration();
		AccelerationAxis& GetZAcceleration();

		PulseCounter& GetVSSPulseCounter();
		PulseDuration& GetInjectorPulseDurationCounter();
		ParkDistanceDecoder& GetParkDistanceDecoder();
		FrequencyCounter& GetRPMFrequencyCounter();

		RotaryEventSource& GetRotaryEventSource();
		SerialEventSource& GetSerialEventSource();

		Voltmeter& GetBatteryVoltageMeter();

	private:
		Configuration m_Configuration;
		PowerManagement m_PowerManagement;

		GraphicContext m_GraphicContext;
		PatternPlayer m_PatternPlayer;
		TimeProvider m_TimeProvider;

		AccelerationAxis m_XAccelerationAxis;
		AccelerationAxis m_YAccelerationAxis;
		AccelerationAxis m_ZAccelerationAxis;

		PulseCounter m_VSSPulseCounter;
		PulseDuration m_InjectorPulseDurationCounter;
		ParkDistanceDecoder m_ParkDistanceDecoder;
		FrequencyCounter m_RPMFrequencyCounter;

		RotaryEventSource m_RotaryEventSource;
		SerialEventSource m_SerialEventSource;

		VoltageDivider m_BatteryVoltageDivider;
		Voltmeter m_BatteryVoltageMeter;
	};
}
