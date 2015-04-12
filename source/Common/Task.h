#pragma once

#include "Common/NonCopyable.h"
#include "Common/List.h"

#include <cinttypes>

namespace Common
{
	class Task
		: public NonCopyable
		, public Common::List<Task>::Element
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
