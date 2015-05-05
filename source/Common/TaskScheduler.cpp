#include "TaskScheduler.h"

void Common::TaskScheduler::Run()
{
    uint32_t now = GetMillisecondCount();

	for (auto&& task : m_Tasks)
    {
    	if (task.CanRun(now))
    	{
    		task.Run(now);
    		break;
    	}
    }
}

void Common::TaskScheduler::Add(Task& task)
{
	m_Tasks.Add(task);
}
