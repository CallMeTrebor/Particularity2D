#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "RenderableObject.hpp"
#include <vector>

class RenderableState {
public:
	std::vector<RenderableObject*> objects;

	~RenderableState();
	RenderableState() {}
	RenderableState(std::vector<RenderableObject*> objects) : objects(objects) {}

	void clear() { objects.clear(); }
};

#endif // !RENDERABLE_HPP