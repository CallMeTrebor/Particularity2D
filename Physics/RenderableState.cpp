#include "RenderableState.hpp"

RenderableState::~RenderableState() {
	for (RenderableObject* object : objects) {
		delete object;
	}
}