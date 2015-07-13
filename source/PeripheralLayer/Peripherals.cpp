#include "Peripherals.h"

#include "HardwareLayer/Hardware.h"

PeripheralLayer::Peripherals::Peripherals(HardwareLayer::Hardware& hardware)
	: m_PowerManagement(hardware)
	, m_GraphicContext(hardware.GetDisplayDriver())
	, m_TimeProvider(hardware.GetTimer())
	, m_XAccelerationAxis(hardware.GetAccelerometerDriver(), m_Configuration, Axis::X)
	, m_YAccelerationAxis(hardware.GetAccelerometerDriver(), m_Configuration, Axis::Y)
	, m_ZAccelerationAxis(hardware.GetAccelerometerDriver(), m_Configuration, Axis::Z)
	, m_VSSPulseCounter(hardware.GetVSSPin())
	, m_RPMPulseCounter(hardware.GetRPMPin())
	, m_RotaryEventSource(hardware.GetRotaryEncoder())
	, m_BatteryVoltageDivider(120000, 33000, 3.3f)
	, m_BatteryVoltageMeter(hardware.GetBatteryVoltagePin(), m_BatteryVoltageDivider)
{
}

const PeripheralLayer::Configuration& PeripheralLayer::Peripherals::GetConfiguration() const
{
	return m_Configuration;
}

PeripheralLayer::PowerManagement& PeripheralLayer::Peripherals::GetPowerManagement()
{
	return m_PowerManagement;
}

PeripheralLayer::GraphicContext& PeripheralLayer::Peripherals::GetGraphicContext()
{
	return m_GraphicContext;
}

PeripheralLayer::TimeProvider& PeripheralLayer::Peripherals::GetTimeProvider()
{
	return m_TimeProvider;
}

PeripheralLayer::AccelerationAxis& PeripheralLayer::Peripherals::GetXAcceleration()
{
	return m_XAccelerationAxis;
}

PeripheralLayer::AccelerationAxis& PeripheralLayer::Peripherals::GetYAcceleration()
{
	return m_YAccelerationAxis;
}

PeripheralLayer::AccelerationAxis& PeripheralLayer::Peripherals::GetZAcceleration()
{
	return m_ZAccelerationAxis;
}

PeripheralLayer::PulseCounter& PeripheralLayer::Peripherals::GetVSSPulseCounter()
{
	return m_VSSPulseCounter;
}

PeripheralLayer::PulseCounter& PeripheralLayer::Peripherals::GetRPMPulseCounter()
{
	return m_RPMPulseCounter;
}

PeripheralLayer::RotaryEventSource& PeripheralLayer::Peripherals::GetRotaryEventSource()
{
	return m_RotaryEventSource;
}

PeripheralLayer::SerialEventSource& PeripheralLayer::Peripherals::GetSerialEventSource()
{
	return m_SerialEventSource;
}

PeripheralLayer::Voltmeter& PeripheralLayer::Peripherals::GetBatteryVoltageMeter()
{
	return m_BatteryVoltageMeter;
}
