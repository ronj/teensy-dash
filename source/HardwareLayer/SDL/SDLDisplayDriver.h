#pragma once

#include "DisplayDriver.h"

#include <memory>
#include <functional>

struct SDL_Window;
struct SDL_Renderer;

namespace HardwareLayer
{
	class SDLDisplayDriver : public DisplayDriver
	{
	public:
		SDLDisplayDriver();

		virtual uint16_t Width() const { return 128; }
		virtual uint16_t Height() const { return 160; }

		virtual void DrawPixel(int16_t x, int16_t y, uint32_t color);
		virtual bool DrawVerticalLine(int16_t, int16_t, int16_t, uint32_t);
		virtual bool DrawHorizontalLine(int16_t, int16_t, int16_t, uint32_t);
		virtual bool FillRect(int16_t, int16_t, int16_t, int16_t, uint32_t);

		virtual void Update();

	private:
		std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> m_Window;
		std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>> m_Renderer;
	};
}
