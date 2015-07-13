#pragma once

#include "List.h"
#include "NonCopyable.h"
#include "Task.h"

namespace Common
{
	class TaskScheduler : public NonCopyable
	{
	public:
	    bool Run(uint32_t now);
		void Add(Task& task);

	private:
		List<Task> m_Tasks;
	};
}
