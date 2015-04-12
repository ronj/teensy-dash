#pragma once

#include "Task.h"

namespace Common
{
	class TimedTask : public Task
	{
	public:
	    inline TimedTask(uint32_t when) : runTime(when) {}
	    virtual bool CanRun(uint32_t now) { return now >= runTime; }
	    inline void SetRunTime(uint32_t when) { runTime = when; }
	    inline void IncrementRunTime(uint32_t inc) { runTime += inc; }
	    inline uint32_t GetRunTime() { return runTime; }

	protected:
	    uint32_t runTime;
	};
}
