#pragma once

#include <cinttypes>

namespace HardwareLayer
{
	class DigitalPin;
}

namespace PeripheralLayer
{
	class TimeProvider;

	class PulseDuration
	{
	public:
		PulseDuration(HardwareLayer::DigitalPin& pin, PeripheralLayer::TimeProvider& time);

		virtual uint32_t GetCount();
		virtual uint32_t GetDuration();
		void GetCountAndDuration(uint32_t& count, uint32_t& duration);

	private:
		void Process();

	private:
		HardwareLayer::DigitalPin& m_Pin;
		PeripheralLayer::TimeProvider& m_Time;

		volatile uint32_t m_Count = 0;
		volatile uint32_t m_Duration = 0;
	};
}
