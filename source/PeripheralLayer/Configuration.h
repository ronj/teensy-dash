#pragma once

#include <cinttypes>

namespace PeripheralLayer
{
	class Configuration
	{
	public:
		template <typename T>
		struct MinMaxCalibration
		{
			MinMaxCalibration(T min, T max) : Min(min), Max(max) {}
			T Min;
			T Max;
		};

		Configuration();

		const MinMaxCalibration<int16_t>& GetAccelerometerXCalibration() const;
		const MinMaxCalibration<int16_t>& GetAccelerometerYCalibration() const;
		const MinMaxCalibration<int16_t>& GetAccelerometerZCalibration() const;

	private:
		MinMaxCalibration<int16_t> m_AccelerometerXCalibration;
		MinMaxCalibration<int16_t> m_AccelerometerYCalibration;
		MinMaxCalibration<int16_t> m_AccelerometerZCalibration;
	};
}
