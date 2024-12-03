#include "Bucket.hpp"

void Bucket::addObject(PhysicsObject* object) {
	objects.push_back(object);
}

void Bucket::removeObject(PhysicsObject* object) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i] == object) {
			objects.erase(objects.begin() + i);
			break;
		}
	}
}