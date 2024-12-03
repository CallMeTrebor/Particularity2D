#ifndef RENDERABLE_ARROW_HPP
#define RENDERABLE_ARROW_HPP
#include "RenderableObject.hpp"

class RenderableArrow : public RenderableObject {
	UIPosition start, end;

public:
	RenderableArrow(int x1, int y1, int x2, int y2, RenderableColor color) :
		RenderableObject(x1, y1, color), start(x1, y1), end(x2, y2) {};
	RenderableArrow(UIPosition start, UIPosition end, RenderableColor color) :
		RenderableObject(start, color), start(start), end(end) {};

	void render(SDL_Renderer* renderer) override;
};

#endif // !RENDERABLE_ARROW_HPP