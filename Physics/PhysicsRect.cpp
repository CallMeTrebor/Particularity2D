#include "PhysicsRect.hpp"
#include "PhysicsProps.hpp"
#include <algorithm>

PhysicsRect::PhysicsRect(PhysicalPosition midPoint, double width, double height, double mass) : PhysicsObject(midPoint, mass) {
	double leftX = midPoint.getX() - width / 2;
	double rightX = midPoint.getX() + width / 2;

	double topY = midPoint.getY() + height / 2;
	double botY = midPoint.getY() - height / 2;

	topLeft = PhysicalPosition(leftX, topY);
	botLeft = PhysicalPosition(leftX, botY);

	topRight = PhysicalPosition(rightX, topY);
	botRight = PhysicalPosition(rightX, botY);

	this->width = width;
	this->height = height;

	momentOfInertia = (mass * (width * width + height * height)) / 12.0;
}

bool PhysicsRect::isPointInside(PhysicalPosition point) {
	return point.getX() >= topLeft.getX() && point.getX() <= topRight.getX() &&
		point.getY() >= botLeft.getY() && point.getY() <= topLeft.getY();
}

std::vector<PhysicalPosition> PhysicsRect::getPoints() {
	return { topLeft, topRight, botLeft, botRight };
}

void PhysicsRect::addForce(Force force, PhysicalPosition applicationPoint){
	velocity += force;

	double rX = applicationPoint.getX() - pos.getX();
	double rY = applicationPoint.getY() - pos.getY();
	double torque = rX * force.getY() - rY * force.getX();

	double angularAcceleration = torque / momentOfInertia;
	angularVelocity += angularAcceleration;
}

void PhysicsRect::applyVelocity(double deltaT, double minX, double minY, double maxX, double maxY) {
	setPos(pos + velocity * deltaT);
	angle += angularVelocity * deltaT;

	double cosA = cos(angle);
	double sinA = sin(angle);

	topLeft = pos + PhysicalPosition(-width / 2 * cosA - height / 2 * sinA, -width / 2 * sinA + height / 2 * cosA);
	topRight = pos + PhysicalPosition(width / 2 * cosA - height / 2 * sinA, width / 2 * sinA + height / 2 * cosA);
	botLeft = pos + PhysicalPosition(-width / 2 * cosA + height / 2 * sinA, -width / 2 * sinA - height / 2 * cosA);
	botRight = pos + PhysicalPosition(width / 2 * cosA + height / 2 * sinA, width / 2 * sinA - height / 2 * cosA);
}

void PhysicsRect::setPos(PhysicalPosition pos) {
	PhysicalPosition delta = pos - this->pos;
	this->pos = pos;

	topLeft += delta;
	topRight += delta;
	botLeft += delta;
	botRight += delta;
}

std::pair<PhysicalPosition, PhysicalPosition> PhysicsRect::getBoundingBox() const {
	PhysicalPosition minPoint(std::min({ topLeft.getX(), topRight.getX(), botLeft.getX(), botRight.getX() }),
		std::min({ topLeft.getY(), topRight.getY(), botLeft.getY(), botRight.getY() }));
	PhysicalPosition maxPoint(std::max({ topLeft.getX(), topRight.getX(), botLeft.getX(), botRight.getX() }),
		std::max({ topLeft.getY(), topRight.getY(), botLeft.getY(), botRight.getY() }));
	return { minPoint, maxPoint };
}