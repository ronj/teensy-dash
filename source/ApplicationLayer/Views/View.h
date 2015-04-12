#pragma once

namespace ApplicationLayer
{
	class DrawEventArgs;

	namespace Views
	{
		class View
		{
		public:
			virtual void OnDraw(DrawEventArgs&) = 0;
		};
	}
}
