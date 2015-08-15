#pragma once

namespace HardwareLayer
{
	class Hardware;
}

namespace PeripheralLayer
{
	class PowerManagement
	{
	public:
		PowerManagement(HardwareLayer::Hardware& hardware);

		void PowerDownPeripherals();
		void PowerUpPeripherals();
		void LowPowerSleep();

	private:
		HardwareLayer::Hardware& m_Hardware;
	};
}
