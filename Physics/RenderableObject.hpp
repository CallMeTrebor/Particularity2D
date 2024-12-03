#ifndef RENDERABLE_OBJECT_HPP
#define RENDERABLE_OBJECT_HPP

#include <SDL2/SDL_render.h>
#include "UIPosition.hpp"

struct RenderableColor {
	uint8_t r, g, b, a;
};

struct RenderableCoord {
	int x;
	int y;
};

class RenderableObject {
protected:
	uint64_t id = 0;
	UIPosition position;
	RenderableColor color;

public:
	RenderableObject() : RenderableObject(0, 0, RenderableColor {255, 255, 255, 255}) {};
	RenderableObject(int x, int y, RenderableColor color) : position(x, y), color(color) {}
	RenderableObject(UIPosition pos, RenderableColor color) : position(pos), color(color) {}

	int getX() const { return position.getX(); }
	int getY() const { return position.getY(); }
	RenderableColor getColor() const { return color; }
	void setColor(RenderableColor color) { this->color = color; }
	uint64_t getId() const { return id; }
	void setId(uint64_t id) { this->id = id; }

	virtual void render(SDL_Renderer* renderer) = 0;
};

#endif // !RENDERABLE_OBJECT_HPP