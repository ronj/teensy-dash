#pragma once

#include "Common/List.h"

namespace ApplicationLayer
{
	class DrawEventArgs;

	namespace Views
	{
		class View
			: public Common::List<View>::Element
		{
		public:
			virtual void OnDraw(DrawEventArgs&) = 0;
			virtual void Query() = 0;

		protected:
			View() : Common::List<View>::Element(*this) { }
		};
	}
}
