#ifndef PHYSICS_PROPS_HPP
#define PHYSICS_PROPS_HPP

#include <cmath>

class PhysicsVector;

class PhysicalPosition {
protected:
	double x, y;

public:
	PhysicalPosition() : x(0), y(0) {};
	PhysicalPosition(double x, double y) : x(x), y(y) {};
	PhysicalPosition(const PhysicalPosition& p) : PhysicalPosition(p.x, p.y) {};

	// offsets the positon by a vector
	void offset(PhysicsVector& offsetVector);
	double getX() const { return x; }
	double getY() const { return y; }

	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }

	PhysicalPosition operator+(const PhysicalPosition& p);
	PhysicalPosition& operator+=(const PhysicalPosition& p);
	PhysicalPosition operator-(const PhysicalPosition& p);
	PhysicalPosition operator*(const double scalar);
	PhysicalPosition operator/(const double scalar);
	bool operator ==(const PhysicalPosition& p) const; 
};

class PhysicsVector : public PhysicalPosition {
public:
	PhysicsVector() : PhysicalPosition(0, 0) {}
	PhysicsVector(const PhysicalPosition& p) : PhysicalPosition(p) {}
	PhysicsVector(const double x, const double y) : PhysicalPosition(x, y) {}
	double dot(const PhysicsVector& v) const { return x * v.x + y * v.y; }
	PhysicsVector cross(const PhysicsVector& v) const { return PhysicsVector(y * v.x - x * v.y, x * v.y - y * v.x); }

	PhysicsVector operator+(const PhysicsVector& v);
	PhysicsVector& operator+=(const PhysicsVector& v);
	PhysicsVector operator*(const double scalar);
	PhysicsVector& operator*=(const double scalar);
	PhysicsVector operator/(const double scalar);

	double magnitude() const { return std::sqrt(x * x + y * y); }
	PhysicsVector& normalize();
};

#endif // !PHYSICS_PROPS_HPP