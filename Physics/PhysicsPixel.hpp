#ifndef PHYSICS_PIXEL
#define PHYSICS_PIXEL

#include "Point.hpp"

// a Pixel is just a point with collision
class PhysicsPixel : public Point {
public:
	PhysicsPixel() : PhysicsPixel(PhysicalPosition(0, 0), 0) {}
	PhysicsPixel(PhysicalPosition pos, double mass) : Point(pos, mass) {}
	PhysicsPixel(const PhysicsPixel& p) : PhysicsPixel(p.pos, p.mass) {}

	bool isPointInside(PhysicalPosition point) override;
	std::vector<PhysicalPosition> getPoints();
};

#endif // !PIXEL_HPP
