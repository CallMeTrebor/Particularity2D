#ifndef BUCKET_HPP
#define BUCKET_HPP

#include <vector>
#include "PhysicsObject.hpp"
#include "PhysicsProps.hpp"

class Bucket {
	std::vector<PhysicsObject*> objects;
	PhysicalPosition leftTop, leftBottom, rightTop, rightBottom;
	Bucket* top = nullptr, * left = nullptr, * right = nullptr, * bottom = nullptr;
public:
	Bucket() : leftTop(0, 0), leftBottom(0, 0), rightTop(0, 0), rightBottom(0, 0) {};
	Bucket(PhysicalPosition leftTop, PhysicalPosition leftBottom, PhysicalPosition rightBottom, PhysicalPosition rightTop) :
		leftTop(leftTop), leftBottom(leftBottom), rightTop(rightTop), rightBottom(rightBottom) {};

	void addObject(PhysicsObject* object);
	void removeObject(PhysicsObject* object);
	void setLeftTop(PhysicalPosition leftTop) { this->leftTop = leftTop; };
	void setLeftBottom(PhysicalPosition leftBottom) { this->leftBottom = leftBottom; };
	void setRightTop(PhysicalPosition rightTop) { this->rightTop = rightTop; };
	void setRightBottom(PhysicalPosition rightBottom) { this->rightBottom = rightBottom; };

	void setTop(Bucket* top) { this->top = top; };
	void setLeft(Bucket* left) { this->left = left; };
	void setRight(Bucket* right) { this->right = right; };
	void setBottom(Bucket* bottom) { this->bottom = bottom; };

	Bucket* getTop() const { return top; }
	Bucket* getLeft() const { return left; }
	Bucket* getRight() const { return right; }
	Bucket* getBottom() const { return bottom; }

	std::vector<PhysicsObject*>& getObjects() { return objects; }

	PhysicsObject* operator[](int index) const { return objects[index]; };
};

#endif // !BUCKET_HPP