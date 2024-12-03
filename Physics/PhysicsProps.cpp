#include "PhysicsProps.hpp"
#include <cmath>

void PhysicalPosition::offset(PhysicsVector& offsetVector) {
	x += offsetVector.getX();
	y += offsetVector.getY();
}

PhysicalPosition PhysicalPosition::operator+(const PhysicalPosition& p) {
	PhysicalPosition newPos(x + p.getX(), y + p.getY());
	return newPos;
};

PhysicalPosition& PhysicalPosition::operator+=(const PhysicalPosition& p) {
	x += p.getX();
	y += p.getY();
	return *this;
}

PhysicalPosition PhysicalPosition::operator-(const PhysicalPosition& p) {
	PhysicalPosition newPos(x - p.getX(), y - p.getY());
	return newPos;
}

PhysicalPosition PhysicalPosition::operator*(const double scalar) {
	return PhysicalPosition (x * scalar, y * scalar);
}

PhysicalPosition PhysicalPosition::operator/(const double scalar)
{
	return PhysicalPosition(x / scalar, y / scalar);
}

const double epsilon = .1;
bool PhysicalPosition::operator ==(const PhysicalPosition& p) const {
	return (std::fabs(x - p.getX()) < epsilon) && (std::fabs(y - p.getY()) < epsilon);
}

PhysicsVector PhysicsVector::operator +(const PhysicsVector& v) {
	return PhysicsVector(x + v.x, y + v.y);
}

PhysicsVector& PhysicsVector::operator +=(const PhysicsVector& v) {
	x += v.x;
	y += v.y;

	return *this;
}

PhysicsVector PhysicsVector::operator *(const double scalar) { 
	return PhysicsVector(x * scalar, y * scalar); 
}

PhysicsVector& PhysicsVector::operator *=(const double scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

PhysicsVector PhysicsVector::operator /(const double scalar) {
	return PhysicsVector(x / scalar, y / scalar);
}

PhysicsVector& PhysicsVector::normalize() {
	double mag = magnitude();
	if (mag != 0) {
		x /= mag;
		y /= mag;
	}
	return *this;
}