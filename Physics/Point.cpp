#include "Point.hpp"

void Point::applyVelocity(double deltaT, double minX, double minY, double maxX, double maxY) {
	PhysicalPosition newPos = pos + velocity * deltaT;
	// for the effects to be visible we need to move the object off the edge by one pixel
	minX++; maxX--; minY++; maxY--;
	if (newPos.getX() < minX) {
		newPos.setX(minX);
		setVelocity(PhysicalPosition(0, velocity.getY()));
	}
	else if (newPos.getX() > maxX) {
		newPos.setX(maxX);
		setVelocity(PhysicalPosition(0, velocity.getY()));
	}

	if (newPos.getY() < minY) {
		newPos.setY(minY);
		setVelocity(PhysicalPosition(velocity.getX(), 0));
	}
	else if (newPos.getY() > maxY) {
		newPos.setY(maxY);
		setVelocity(PhysicalPosition(velocity.getX(), 0));
	}

    pos = newPos;
}

void Point::addForce(Force force, PhysicalPosition applicationPoint = PhysicalPosition(0, 0)) {
	velocity += force;
}