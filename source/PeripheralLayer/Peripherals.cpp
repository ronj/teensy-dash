#include "Peripherals.h"

#include "HardwareLayer/Hardware.h"

PeripheralLayer::Peripherals::Peripherals(HardwareLayer::Hardware& hardware)
	: m_GraphicContext(hardware.GetDisplayDriver())
	, m_TimeProvider(hardware.GetTimer())
	, m_XAccelerationAxis(hardware.GetAccelerometerDriver(), m_Configuration, Axis::X)
	, m_YAccelerationAxis(hardware.GetAccelerometerDriver(), m_Configuration, Axis::Y)
	, m_ZAccelerationAxis(hardware.GetAccelerometerDriver(), m_Configuration, Axis::Z)
{
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
