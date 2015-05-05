#pragma once

#include "List.h"
#include "NonCopyable.h"
#include "Task.h"

#include <functional>

namespace Common
{
	class TaskScheduler : public NonCopyable
	{
	public:
	    void Run();
		void Add(Task& task);

	    std::function<uint32_t()> GetMillisecondCount;

	private:
		List<Task> m_Tasks;
	};
}
