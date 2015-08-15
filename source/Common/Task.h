#pragma once

#include "List.h"
#include "NonCopyable.h"

#include <cinttypes>

namespace Common
{
	class Task
		: public Common::List<Task>::Element
		, public Common::NonCopyable
	{
	public:
	    virtual bool CanRun(uint32_t now) = 0;
	    virtual void Run(uint32_t now) = 0;

	protected:
		Task()
			: Common::List<Task>::Element(*this)
		{
		}
	};
}
