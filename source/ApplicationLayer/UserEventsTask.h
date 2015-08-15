#pragma once

#include "Common/Task.h"
#include "Common/List.h"

#include "PeripheralLayer/EventSource.h"

#include <cinttypes>
#include <functional>

namespace PeripheralLayer
{
	class Peripherals;
}

namespace ApplicationLayer
{
	class UserEventsTask : public Common::Task
	{
	public:
		UserEventsTask(PeripheralLayer::Peripherals& peripherals);

		bool CanRun(uint32_t);
		void Run(uint32_t now);

		std::function<void()> OnNext;
		std::function<void()> OnPrevious;
		std::function<void()> OnShortPress;
		std::function<void()> OnLongPress;
		std::function<void()> OnQuery;
		std::function<void()> OnQuit;

	private:
		template <typename Func>
		void CallWrapper(Func&& f)
		{
			if (f) f();
		}

	private:
		Common::List<PeripheralLayer::EventSource> m_EventSources;
	};
}
