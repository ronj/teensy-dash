#pragma once

namespace PeripheralLayer
{
	class GraphicContex;
}

namespace ApplicationLayer
{
	struct PaletteEntry;

	class DrawEventArgs
	{
	public:
		DrawEventArgs(PeripheralLayer::GraphicContext& context, const PaletteEntry& theme)
			: graphicContext(context)
			, colorScheme(theme)
		{
		}
		
		PeripheralLayer::GraphicContext& graphicContext;
		const ApplicationLayer::PaletteEntry& colorScheme;
	};
}
