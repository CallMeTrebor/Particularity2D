#include "Gravity.hpp"
#include "PhysicsObject.hpp"
#include "Force.hpp"

void Gravity::enactInfluence(PhysicsObject& obj) {
	// apply gravity force to object
	if (!obj.isAffectedByGravity()) return;
	obj.addForce(Force(magnitude*gravityDirection.getX(), magnitude*gravityDirection.getY()), obj.getPos());
}