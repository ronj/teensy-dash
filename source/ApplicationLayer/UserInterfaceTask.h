#pragma once

#include "ApplicationLayer/Palette.h"

#include "Common/TimedTask.h"

namespace PeripheralLayer
{
	class GraphicContext;
}

namespace ApplicationLayer
{
	class ModelCollection;

	class UserInterfaceTask : public Common::TimedTask
	{
	public:
		UserInterfaceTask(PeripheralLayer::GraphicContext& context, ApplicationLayer::ModelCollection& models, uint32_t now);

		void Run(uint32_t now);

	private:
		PeripheralLayer::GraphicContext& m_GraphicContext;
		ApplicationLayer::ModelCollection& m_Models;
		ApplicationLayer::PaletteEntry m_Palette;
	};
}
