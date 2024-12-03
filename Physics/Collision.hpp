#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "PhysicsObject.hpp"
#include "PhysicsRect.hpp"
#include "PhysicsPixel.hpp"

namespace Collision {
	class CollisionNotImplemented : public std::exception {};

	bool handleCollision(PhysicsRect* rect1, PhysicsRect* rect2);
	bool handleCollision(PhysicsPixel* pixel1, PhysicsPixel* pixel2);
	bool handleCollision(PhysicsPixel* obj1, PhysicsRect* obj2);
	bool handleCollision(PhysicsObject* obj1, PhysicsObject* obj2);
};
#endif // !COLLISION_HPP
