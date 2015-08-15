#pragma once

#include "Config.h"

namespace Common
{
	class NonCopyable
	{
	protected:
		NonCopyable() CFG_DECL_DEFAULT;

	private:
	  NonCopyable(const NonCopyable&) CFG_DECL_DELETE;
	  const NonCopyable& operator=(const NonCopyable&) CFG_DECL_DELETE;
	};
}
