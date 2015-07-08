#pragma once

#include <array>
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

		virtual uint16_t GetTireWidth() const;
		virtual uint8_t GetTireAspect() const;
		virtual uint8_t GetRimSize() const;

		virtual float GetFinalDriveRatio() const;
		virtual const std::array<float, 6>& GetGearRatios() const;
		static float UnavailableGear();

		virtual uint16_t GetVSSPulsesPerKm() const;

	private:
		MinMaxCalibration<int16_t> m_AccelerometerXCalibration;
		MinMaxCalibration<int16_t> m_AccelerometerYCalibration;
		MinMaxCalibration<int16_t> m_AccelerometerZCalibration;

		uint16_t m_TireWidth;
		uint8_t m_TireAspect;
		uint8_t m_RimSize;

		float m_FinalDrive;
		std::array<float, 6> m_GearRatios;

		uint16_t m_VSSPulsesPerKm;
	};
}
