#include "GravityWell.hpp"
#include "PhysicsObject.hpp"
#include "Force.hpp"
#include <cmath>

void GravityWell::enactInfluence(PhysicsObject& obj) {
	if(!obj.isAffectedByGravity()) return;
	double dx = sourcePosition.getX() - obj.getPos().getX();
	double dy = sourcePosition.getY() - obj.getPos().getY();

	double length = std::sqrt(dx * dx + dy * dy);
	dx /= length;
	dy /= length;

	obj.addForce(Force(dx * magnitude, dy * magnitude), obj.getPos());
}