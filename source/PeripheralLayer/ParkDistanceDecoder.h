#pragma once

#include <cinttypes>

namespace HardwareLayer
{
	class DigitalPin;
}

namespace PeripheralLayer
{
	class TimeProvider;

	class ParkDistanceDecoder
	{
	public:
		ParkDistanceDecoder(HardwareLayer::DigitalPin& pin, PeripheralLayer::TimeProvider& time);

		virtual uint32_t GetPackedDistances() const;

	private:
		void Decode();

	private:
		HardwareLayer::DigitalPin& m_Pin;
		PeripheralLayer::TimeProvider& m_Time;

		volatile uint32_t m_PackedDistances = 0;
	};
}
