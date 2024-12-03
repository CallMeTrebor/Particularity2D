#ifndef RENDERABLE_PIXEL_HPP
#define RENDERABLE_PIXEL_HPP

#include "RenderableObject.hpp"

class RenderablePixel : public RenderableObject {
public:
	RenderablePixel() : RenderableObject() {};
	RenderablePixel(int x, int y, RenderableColor color) : RenderableObject(x, y, color) {};
	RenderablePixel(UIPosition pos, RenderableColor color) : RenderableObject(pos, color) {};

	void render(SDL_Renderer* renderer) override;
};

#endif // !RENDERABLE_PIXEL_HPP