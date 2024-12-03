#ifndef PHYSICAL_RECT_HPP
#define PHYSICAL_RECT_HPP

#include "PhysicsObject.hpp"
#include "Point.hpp"

class PhysicsRect : public PhysicsObject {
protected:
	double width;
	double height;
	PhysicalPosition topLeft, topRight, botLeft, botRight;
	
public:
	PhysicsRect() : PhysicsRect(PhysicalPosition(0, 0), 5, 5, 1) {}
	PhysicsRect(PhysicalPosition midPoint, double width, double height, double mass);

	bool isPointInside(PhysicalPosition point) override;
	void setPos(PhysicalPosition pos) override;
	std::vector<PhysicalPosition> getPoints() override;
	void addForce(Force force, PhysicalPosition applicationPoint) override;
	void applyVelocity(double deltaT, double minX, double minY, double maxX, double maxY) override;

	PhysicalPosition getTopLeft() const { return topLeft; }
	PhysicalPosition getTopRight() const { return topRight; }
	PhysicalPosition getBotLeft() const { return botLeft; }
	PhysicalPosition getBotRight() const { return botRight; }

	double getWidth() const { return width; }
	double getHeight() const { return height; }

	std::pair<PhysicalPosition, PhysicalPosition> getBoundingBox() const;
};


#endif // !PHYSICAL_RECT_HPP
