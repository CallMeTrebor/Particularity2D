#include "RenderableArrow.hpp"

void RenderableArrow::render(SDL_Renderer* renderer) {
	auto [r, g, b, a] = color;
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawLine(renderer, start.getX(), start.getY(), end.getX(), end.getY());

	// Draw the arrow head
	double angle = atan2(end.getY() - start.getY(), end.getX() - start.getX());
	double arrowLength = 10;
	double arrowAngle = 0.5;
	SDL_RenderDrawLine(renderer, end.getX(), end.getY(), end.getX() - arrowLength * cos(angle - arrowAngle), end.getY() - arrowLength * sin(angle - arrowAngle));
	SDL_RenderDrawLine(renderer, end.getX(), end.getY(), end.getX() - arrowLength * cos(angle + arrowAngle), end.getY() - arrowLength * sin(angle + arrowAngle));
}