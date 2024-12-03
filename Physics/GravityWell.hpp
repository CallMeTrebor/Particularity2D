#ifndef GRAVITY_WELL_HPP
#define GRAVITY_WELL_HPP

#include "LocalInfluence.hpp"
#include "PhysicsObject.hpp"
#include "PhysicsProps.hpp"

class GravityWell : public LocalInfluence {
public:
	GravityWell() : GravityWell(PhysicalPosition(), 0) {}
	GravityWell(PhysicalPosition source, double magnitude) : LocalInfluence(source, magnitude) {}

	void enactInfluence(PhysicsObject& obj) override;
};

#endif // !GRAVITY_WELL_HPP