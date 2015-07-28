#pragma once

#include "Common/TimedTask.h"

namespace PeripheralLayer
{
	class GraphicContext;
}

namespace ApplicationLayer
{
	struct PaletteEntry;
	class ViewCollection;

	namespace Views
	{
		class View;
	}

	class UserInterfaceTask
		: public Common::TimedTask
	{
	public:
		UserInterfaceTask(PeripheralLayer::GraphicContext& context, ViewCollection& views, uint32_t now);

		void NextScreen();
		void PreviousScreen();
		void QueryScreen();

		void Run(uint32_t);

	private:
		PeripheralLayer::GraphicContext& m_GraphicContext;
		const PaletteEntry& m_Palette;
		ViewCollection& m_Views;
		Views::View* m_CurrentScreen;
	};
}
