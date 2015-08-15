#include "TaskScheduler.h"

bool Common::TaskScheduler::Run(uint32_t now)
{
	for (auto&& task : m_Tasks)
    {
    	if (task.CanRun(now))
    	{
    		task.Run(now);
            return true;
    	}
    }

    return false;
}

void Common::TaskScheduler::Add(Task& task)
{
	m_Tasks.Add(task);
}
