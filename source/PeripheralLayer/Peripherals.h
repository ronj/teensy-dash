#pragma once

#include "Configuration.h"
#include "GraphicContext.h"
#include "TimeProvider.h"
#include "AccelerationAxis.h"
#include "PulseCounter.h"

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

	private:
		Configuration m_Configuration;

		GraphicContext m_GraphicContext;
		TimeProvider m_TimeProvider;

		AccelerationAxis m_XAccelerationAxis;
		AccelerationAxis m_YAccelerationAxis;
		AccelerationAxis m_ZAccelerationAxis;

		PulseCounter m_VSSPulseCounter;
	};
}
