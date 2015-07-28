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
			extern const uint8_t OilCanData[];
		}

		static const Bitmap WaterTemperature { 35, 32, internal::WaterTemperatureData };
		static const Bitmap TripDistance { 30, 24, internal::TripDistanceData };
		static const Bitmap Battery { 35, 23, internal::BatteryData };
		static const Bitmap FuelPump { 26, 26, internal::FuelPumpData };
		static const Bitmap OilCan { 32, 32, internal::OilCanData };
	}
}
