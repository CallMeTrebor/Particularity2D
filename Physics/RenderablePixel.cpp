#include "RenderablePixel.hpp"

void RenderablePixel::render(SDL_Renderer* renderer) {
	auto [r, g, b, a] = color;
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawPoint(renderer, getX(), getY());
}