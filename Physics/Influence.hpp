#ifndef INFLUENCE_H
#define INFLUENCE_H

#include "PhysicsObject.hpp"
#include "Force.hpp"

class Influence {
protected:
	double magnitude;
public:
	Influence() : magnitude(0) {}
	Influence(double magnitude) : magnitude(magnitude) {}
	virtual void enactInfluence(PhysicsObject& obj) = 0;

	double getMagnitude() const { return magnitude; }
	void setMagnitude(double magnitude) { this->magnitude = magnitude; }
};

#endif // INFLUENCE_H