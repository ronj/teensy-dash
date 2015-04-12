#pragma once

namespace Common
{
	class NonCopyable
	{
	protected:
	  NonCopyable() = default;

	private:
	  NonCopyable(const NonCopyable&) = delete;
	  const NonCopyable& operator=(const NonCopyable&) = delete;
	};
}
