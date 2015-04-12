#pragma once

#include "Configuration.h"
#include "GraphicContext.h"
#include "TimeProvider.h"
#include "AccelerationAxis.h"

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

		GraphicContext& GetGraphicContext();
		TimeProvider& GetTimeProvider();

		AccelerationAxis& GetXAcceleration();
		AccelerationAxis& GetYAcceleration();
		AccelerationAxis& GetZAcceleration();

	private:
		Configuration m_Configuration;

		GraphicContext m_GraphicContext;
		TimeProvider m_TimeProvider;

		AccelerationAxis m_XAccelerationAxis;
		AccelerationAxis m_YAccelerationAxis;
		AccelerationAxis m_ZAccelerationAxis;
	};
}
