#pragma once

#include <cinttypes>

namespace HardwareLayer
{
	class AccelerometerDriver;
}

namespace PeripheralLayer
{
	enum class Axis { X, Y, Z };

	class Configuration;

	class AccelerationAxis
	{
	public:
		AccelerationAxis(HardwareLayer::AccelerometerDriver& driver, Configuration& configuration, Axis axis);
		
		int32_t GetValue() const;

	private:
		HardwareLayer::AccelerometerDriver& m_Driver;
		Configuration& m_Configuration;
		Axis m_Axis;
	};
}
