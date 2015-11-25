#pragma once

#include "DashCompilerDetection.h"
#include "List.h"

#include <cinttypes>

namespace Common
{
	class Task : public Common::List<Task>::Element
	{
	public:
		Task(const Task&) CFG_DELETED_FUNCTION;
		Task& operator=(const Task&) CFG_DELETED_FUNCTION;

	    virtual bool CanRun(uint32_t now) = 0;
	    virtual void Run(uint32_t now) = 0;

	protected:
		Task()
			: Common::List<Task>::Element(*this)
		{
		}
	};
}
