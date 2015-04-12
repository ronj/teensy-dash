#pragma once

#include "Common/Task.h"

#include <cinttypes>

namespace ApplicationLayer
{
	class UserEventsTask : public Common::Task
	{
	public:
		UserEventsTask();

		bool CanRun(uint32_t);
		void Run(uint32_t now);

	private:
		int32_t m_PreviousEncoderValue = 0;
		int32_t m_CurrentEncoderValue = 0;
	};
}
