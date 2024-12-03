#include "PhysicsPixel.hpp"
#include <vector>

bool PhysicsPixel::isPointInside(PhysicalPosition point) {
	return point == pos;
}

std::vector<PhysicalPosition> PhysicsPixel::getPoints() {
	return std::vector<PhysicalPosition>(1, pos);
}