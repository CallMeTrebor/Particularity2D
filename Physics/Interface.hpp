#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "RenderablePixel.hpp"
#include "RenderableState.hpp"
#include "PhysicsPixel.hpp"
#include "Engine.hpp"
#include "RenderableRect.hpp"
#include "PhysicsRect.hpp"
#include <stdexcept>

class UnknownObjectType : public std::exception {};

RenderablePixel* createRenderablePixel(PhysicsPixel pixel, RenderableColor color);
RenderableRect* createRenderableRect(PhysicsRect rect, RenderableColor color);
RenderableState* physicalStateToRenderableState(PhysicalState state);

#endif // !INTERFACE_HPP
