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

		virtual uint16_t GetInjectorFlow() const;
		virtual uint8_t GetInjectorCount() const;
		virtual uint8_t GetInjectorMechanicalDelay() const;
		virtual uint16_t GetFuelPressure() const;
		virtual uint32_t GetMicrosecondsPerLiter() const;

	private:
		MinMaxCalibration<int16_t> m_AccelerometerXCalibration;
		MinMaxCalibration<int16_t> m_AccelerometerYCalibration;
		MinMaxCalibration<int16_t> m_AccelerometerZCalibration;

		uint16_t m_TireWidth; /* In cm */
		uint8_t m_TireAspect; /* As percentage */
		uint8_t m_RimSize;    /* In inch */

		float m_FinalDrive;
		std::array<float, 6> m_GearRatios;

		uint16_t m_VSSPulsesPerKm;

		uint16_t m_InjectorFlow; /* In cm3/min * 10 i.e. 149.3 cc/min = 1493 */
		uint8_t m_InjectorCount;
		uint8_t m_InjectorMechanicalDelay; /* In uSec */
		uint16_t m_FuelPressure; /* In mBar */
	};
}
