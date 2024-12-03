#ifndef STATIC_OBJECT_HPP
#define STATIC_OBJECT_HPP

#include "PhysicsProps.hpp"

class StaticObject {
protected:
	uint64_t id = 0;
	PhysicalPosition pos;
	double angle = 0.;

public:
	StaticObject() : StaticObject(PhysicalPosition(0, 0), 0) {}
	StaticObject(PhysicalPosition pos, double angle) : pos(pos), angle(angle) {}

	virtual void setPos(PhysicalPosition pos) { this->pos = pos; }
	virtual PhysicalPosition getPos(PhysicalPosition) { return pos; }
	virtual void setAngle(double angle) { this->angle = angle; }
	virtual double getAngle() { return angle; }
	virtual bool isPointInside(PhysicalPosition point) = 0;
};

#endif // !STATIC_OBJECT_HPP
