#include "StaticRect.hpp"
#include "PhysicsRect.hpp"

bool StaticRect::isPointInside(PhysicalPosition point){
	return point.getX() >= topLeft.getX() && point.getX() <= topRight.getX() &&
		point.getY() >= botLeft.getY() && point.getY() <= topLeft.getY();
}

StaticRect::operator PhysicsRect() const {
	return PhysicsRect(pos, width, height, 1);
}