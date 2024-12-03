#include "Force.hpp"

Force Force::operator +(const Force& v) {
	return Force(x + v.x, y + v.y);
}

Force& Force::operator +=(const Force& v) {
	x += v.x;
	y += v.y;
	return *this;
}

Force Force::operator *(const double scalar) {
	return Force(x * scalar, y * scalar);
}

Force& Force::operator *=(const double scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}