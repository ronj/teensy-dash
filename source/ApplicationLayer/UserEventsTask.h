#pragma once

#include <Encoder.h>
#undef PI

#include "Common/Task.h"

#include <cinttypes>
#include <functional>

namespace ApplicationLayer
{
	class UserEventsTask : public Common::Task
	{
	public:
		UserEventsTask();

		bool CanRun(uint32_t);
		void Run(uint32_t now);

		std::function<void()> OnNext;
		std::function<void()> OnPrevious;
		std::function<void()> OnShortPress;
		std::function<void()> OnLongPress;

	private:
		void CallOnNext();
		void CallOnPrevious();

	private:
		int32_t m_CurrentEncoderValue;
		int32_t m_PreviousEncoderValue;
		Encoder m_Encoder;
	};
}
