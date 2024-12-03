#include "RenderableRect.hpp"

void RenderableRect::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_RenderDrawLine(renderer, topLeft.getX(), topLeft.getY(), topRight.getX(), topRight.getY());
	SDL_RenderDrawLine(renderer, topRight.getX(), topRight.getY(), botRight.getX(), botRight.getY());
	SDL_RenderDrawLine(renderer, botRight.getX(), botRight.getY(), botLeft.getX(), botLeft.getY());
	SDL_RenderDrawLine(renderer, botLeft.getX(), botLeft.getY(), topLeft.getX(), topLeft.getY());
}