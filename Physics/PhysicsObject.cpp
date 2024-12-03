#include "PhysicsObject.hpp"

void PhysicsObject::addTorque(double torque) {
	double angularAcceleration = torque / momentOfInertia;
	angularVelocity += angularAcceleration;
}