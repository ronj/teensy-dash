#pragma once

#include "ApplicationLayer/Palette.h"

#include "Common/TimedTask.h"

namespace PeripheralLayer
{
	class GraphicContext;
}

namespace ApplicationLayer
{
	class ViewCollection;

	namespace Views
	{
		class View;
	}

	class UserInterfaceTask : public Common::TimedTask
	{
	public:
		UserInterfaceTask(PeripheralLayer::GraphicContext& context, ApplicationLayer::ViewCollection& views, uint32_t now);

		void NextScreen();
		void PreviousScreen();

		void Run(uint32_t now);

	private:
		PeripheralLayer::GraphicContext& m_GraphicContext;
		const ApplicationLayer::PaletteEntry& m_Palette;
		ApplicationLayer::ViewCollection& m_Views;
		Views::View* m_CurrentScreen;
	};
}
