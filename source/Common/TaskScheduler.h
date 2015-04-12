#pragma once

#include "Task.h"

#include "Common/NonCopyable.h"
#include "Common/List.h"

#undef swap
#undef min
#undef max

#include <functional>

namespace Common
{
	class TaskScheduler : public NonCopyable
	{
	public:
	    void Run()
    	{
	        uint32_t now = GetMillisecondCount();

			for (auto&& task : m_Tasks)
	        {
	        	if (task.CanRun(now))
	        	{
	        		task.Run(now);
	        		//break;
	        	}
	        }
		}

		void Add(Task& task)
		{
			m_Tasks.Add(task);
		}

	    std::function<uint32_t()> GetMillisecondCount;

	private:
		Common::List<Task> m_Tasks;
	};
}
