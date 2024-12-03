#ifndef RENDERABLE_RECT_HPP
#define RENDERABLE_RECT_HPP

#include "RenderableObject.hpp"
class RenderableRect : public RenderableObject {
	UIPosition topLeft, topRight, botLeft, botRight;
public:
	RenderableRect(UIPosition center, UIPosition topLeft, UIPosition topRight, UIPosition botLeft,
		UIPosition botRight, RenderableColor color) : 
		RenderableObject(center, color), topLeft(topLeft), topRight(topRight), botLeft(botLeft), botRight(botRight) {}

	void render(SDL_Renderer* renderer) override;
};

#endif // !RENDERABLE_RECT_HPP
