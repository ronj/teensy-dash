#pragma once

#include "DashCompilerDetection.h"
#include "List.h"
#include "Task.h"

namespace Common
{
	class TaskScheduler
	{
	public:
		TaskScheduler() = default;
		TaskScheduler(const TaskScheduler&) CFG_DELETED_FUNCTION;
		TaskScheduler& operator=(const TaskScheduler&) CFG_DELETED_FUNCTION;

	    bool Run(uint32_t now);
		void Add(Task& task);

	private:
		List<Task> m_Tasks;
	};
}
