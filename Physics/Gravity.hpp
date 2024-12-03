#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include "GlobalInfluence.hpp"
#include "PhysicsProps.hpp"
#include "PhysicsObject.hpp"

class Gravity : public GlobalInfluence {
	PhysicsVector gravityDirection;
public:
	Gravity() : Gravity(9.81, PhysicsVector(0, 1)) {}
	Gravity(const double& g, PhysicsVector gravityDirection) : GlobalInfluence(g), gravityDirection(gravityDirection.normalize()) {}

	void setGravityDirection(const PhysicsVector& gravityDirection) { this->gravityDirection = gravityDirection; }
	PhysicsVector getGravityDirection() const { return gravityDirection; }

	void enactInfluence(PhysicsObject& obj) override;
};

#endif // !GRAVITY_HPP
