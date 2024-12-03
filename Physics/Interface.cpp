#include "Interface.hpp"
#include "RenderableRect.hpp"
#include "PhysicsRect.hpp"
#include "PhysicsPixel.hpp"
#include "StaticRect.hpp"
#include <SDL2/SDL.h>

RenderablePixel* createRenderablePixel(PhysicsPixel pixel, RenderableColor color = RenderableColor(255, 255, 255, 255)) {
	return new RenderablePixel((int)pixel.getPos().getX(), (int)pixel.getPos().getY(), color);
}

RenderableRect* createRenderableRect(PhysicsRect rect, RenderableColor color = RenderableColor(255, 255, 255, 255)) {
	UIPosition center(rect.getPos().getX(), rect.getPos().getY());
	UIPosition topLeft(rect.getTopLeft().getX(), rect.getTopLeft().getY());
	UIPosition topRight(rect.getTopRight().getX(), rect.getTopRight().getY());
	UIPosition botLeft(rect.getBotLeft().getX(), rect.getBotLeft().getY());
	UIPosition botRight(rect.getBotRight().getX(), rect.getBotRight().getY());

	return new RenderableRect(center, topLeft, topRight, botLeft, botRight, color);
}

RenderableState* physicalStateToRenderableState(PhysicalState state) {
	RenderableState* ret = new RenderableState;
	for (PhysicsObject* obj : state.objects) {
		if (obj == nullptr) continue;
		RenderableObject* renderable = nullptr;
		if (dynamic_cast<PhysicsPixel*>(obj)) {
			renderable = createRenderablePixel(*(PhysicsPixel*) obj);
		}
		else if (dynamic_cast<PhysicsRect*>(obj)) {
			renderable = createRenderableRect(*(PhysicsRect*) obj);
		}
		else if (dynamic_cast<StaticRect*>(obj)) {
			renderable = createRenderableRect(*(PhysicsRect*) obj);
		}
		else throw UnknownObjectType();
		renderable->setId(obj->getId());
		ret->objects.push_back(renderable);
	}

	return ret;
}