#pragma once

#include "Task.h"

namespace Common
{
	class TimedTask : public Task
	{
	public:
	    TimedTask(uint32_t when);

	    virtual bool CanRun(uint32_t now);
	    void IncrementRunTime(uint32_t inc);

	protected:
	    uint32_t m_Runtime;
	};
}
