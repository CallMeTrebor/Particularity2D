#ifndef STATIC_RECT_HPP

#include "StaticObject.hpp"
#include "PhysicsRect.hpp"

class StaticRect : public StaticObject {
protected:
	double width;
	double height;
	PhysicalPosition topLeft, topRight, botLeft, botRight;

public:
	bool isPointInside(PhysicalPosition point) override;

	double getWidth() const { return width; };
	double getHeight() const { return height; };

	operator PhysicsRect() const;
};

#endif // !STATIC_RECT_HPP
