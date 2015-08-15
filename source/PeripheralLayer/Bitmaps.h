#pragma once

#include "Bitmap.h"

namespace PeripheralLayer
{
	namespace Bitmaps
	{
		namespace internal
		{
			extern const uint8_t WaterTemperatureData[];
			extern const uint8_t TripDistanceData[];
			extern const uint8_t BatteryData[];
			extern const uint8_t FuelPumpData[];
			extern const uint8_t TimespanData[];
			extern const uint8_t AverageSpeedData[];
			extern const uint8_t BigWarningData[];
			extern const uint8_t BigCarData[];
			extern const uint8_t OilCanData[];
		}

		static const Bitmap WaterTemperature { 35, 32, internal::WaterTemperatureData };
		static const Bitmap TripDistance { 27, 26, internal::TripDistanceData };
		static const Bitmap Battery { 35, 23, internal::BatteryData };
		static const Bitmap FuelPump { 26, 26, internal::FuelPumpData };
		static const Bitmap Timespan { 30, 27, internal::TimespanData };
		static const Bitmap AverageSpeed { 30, 29, internal::AverageSpeedData };
		static const Bitmap BigWarning { 100, 88, internal::BigWarningData };
		static const Bitmap BigCar { 46, 89, internal::BigCarData };
		static const Bitmap OilCan { 32, 32, internal::OilCanData };
	}
}
