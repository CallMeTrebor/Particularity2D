#ifndef FORCE_HPP
#define FORCE_HPP

#include "PhysicsProps.hpp"

class Force : public PhysicsVector {
public:
	Force() : Force(0, 0) {}
	Force(const double x, const double y) : PhysicsVector(x, y) {};
	Force operator +(const Force& v);
	Force& operator +=(const Force& v);
	Force operator *(const double scalar);
	Force& operator *=(const double scalar);
};

#endif // !FORCE_HPP
