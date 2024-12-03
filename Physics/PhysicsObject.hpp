#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

#include "PhysicsProps.hpp"
#include "Force.hpp"
#include <vector>

class PhysicsObject {
protected:
	uint64_t id = 0;
	PhysicalPosition pos;
	PhysicsVector velocity;
	double mass = 1.;
	double angle = 0.;             
	double angularVelocity = 0.;   
	double momentOfInertia = 0.; 
	bool affectedByGravity = true;

public:
	PhysicsObject() : PhysicsObject(PhysicalPosition(0, 0), 0) {}
	PhysicsObject(PhysicalPosition pos, double mass) :
		pos(pos), mass(mass), velocity(0, 0) {}

	virtual void addForce(Force force, PhysicalPosition applicationPoint) = 0;
	virtual void applyVelocity(double deltaT, double minX, double minY, double maxX, double maxY) = 0;
	virtual bool isPointInside(PhysicalPosition point) = 0;
	virtual std::vector<PhysicalPosition> getPoints() = 0;
	virtual void setPos(PhysicalPosition pos) { this->pos = pos; }

	void addTorque(double torque);
	PhysicalPosition getPos() const { return pos; }
	void setMass(double mass) { this->mass = mass; }
	double getMass() const { return mass; }
	PhysicsVector getVelocity() const { return velocity; }
	void setVelocity(PhysicsVector velocity) { this->velocity = velocity; }
	uint64_t getId() const { return id; }
	void setId(uint64_t id) { this->id = id; }
	double getAngle() const { return angle; }
	bool isAffectedByGravity() const { return affectedByGravity; }
	void setAffectedByGravity(bool affectedByGravity) { this->affectedByGravity = affectedByGravity; }

	double getAngularVelocity() const { return angularVelocity; }
	double getMomentOfInertia() const { return momentOfInertia; }
	void setAngle(double angle) { this->angle = angle; }
	void setAngularVelocity(double angularVelocity) { this->angularVelocity = angularVelocity; }
	void setMomentOfInertia(double momentOfInertia) { this->momentOfInertia = momentOfInertia; }
};

#endif