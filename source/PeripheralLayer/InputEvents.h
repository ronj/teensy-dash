#pragma once

namespace PeripheralLayer
{
	class InputEvents
	{
	public:
		enum class EventType { Next, Previous, ShortPress, LongPress };

		bool EventAvailable();
		EventType GetEvent();
	};
}