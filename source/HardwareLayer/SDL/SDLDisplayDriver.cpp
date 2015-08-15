#include "SDLDisplayDriver.h"

#include <SDL.h>

HardwareLayer::SDLDisplayDriver::SDLDisplayDriver()
{
	SDL_Window* rawWindow = nullptr;
	SDL_Renderer* rawRenderer = nullptr;

	SDL_CreateWindowAndRenderer(Width(), Height(), SDL_WINDOW_SHOWN, &rawWindow, &rawRenderer);

	m_Window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(rawWindow, SDL_DestroyWindow);
	m_Renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>>(rawRenderer, SDL_DestroyRenderer);
}

void HardwareLayer::SDLDisplayDriver::DrawPixel(int16_t x, int16_t y, uint32_t color)
{
	SDL_SetRenderDrawColor(m_Renderer.get(), (color >> 24) & 0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
	SDL_RenderDrawPoint(m_Renderer.get(), x, y);
}

bool HardwareLayer::SDLDisplayDriver::DrawVerticalLine(int16_t x, int16_t y, int16_t h, uint32_t color)
{
	return false;
}

bool HardwareLayer::SDLDisplayDriver::DrawHorizontalLine(int16_t x, int16_t y, int16_t w, uint32_t color)
{
	return false;
}

bool HardwareLayer::SDLDisplayDriver::FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)
{
	return false;
}

void HardwareLayer::SDLDisplayDriver::Update()
{
	SDL_RenderPresent(m_Renderer.get());
}
