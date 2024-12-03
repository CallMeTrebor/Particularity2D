#ifndef POINT_HPP
#define POINT_HPP

#include "PhysicsObject.hpp"
#include "PhysicsRect.hpp"

// A point is the smallest possible object, it has no collision with other points as it is infimatesimally small
// if you want a point that can also collide, you need to look at a Pixel
// both appera as one pixel on screen, but making the point appear is purely for representation purposes
class Point : public PhysicsObject {
public:
	Point() : Point(PhysicalPosition(0, 0), 0) {}
	Point(PhysicalPosition pos, double mass) : PhysicsObject(pos, mass) {}
	Point(const Point& p) : Point(p.pos, p.mass) {}

	void applyVelocity(double deltaT, double minX, double minY, double maxX, double maxY) override;
	void addForce(Force force, PhysicalPosition applicationPoint) override;
};

#endif // !POINT_HPP