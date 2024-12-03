#include "Collision.hpp"
#include "PhysicsRect.hpp"
#include "PhysicsPixel.hpp"

bool Collision::handleCollision(PhysicsObject* obj1, PhysicsObject* obj2) {
    if (obj1 == obj2) return false;

	PhysicsRect* rect1 = dynamic_cast<PhysicsRect*>(obj1);
	PhysicsRect* rect2 = dynamic_cast<PhysicsRect*>(obj2);
	PhysicsPixel* pixel1 = dynamic_cast<PhysicsPixel*>(obj1);
	PhysicsPixel* pixel2 = dynamic_cast<PhysicsPixel*>(obj2);

	if (rect1 && rect2) return Collision::handleCollision(rect1, rect2);
	if (pixel1 && pixel2) return Collision::handleCollision(pixel1, pixel2);
	if (pixel1 && rect2) return Collision::handleCollision(pixel1, rect2);
	if (pixel2 && rect1) return Collision::handleCollision(pixel2, rect1);

	throw Collision::CollisionNotImplemented();
}

bool Collision::handleCollision(PhysicsPixel* pixel, PhysicsRect* rect) {
    PhysicalPosition pixelPos = pixel->getPos();

    if (rect->isPointInside(pixelPos)) {
        // Get the bounding box of the rectangle
        auto [rectMin, rectMax] = rect->getBoundingBox();

        // Determine the shortest way to move the pixel out of the rectangle
        double leftDist = pixelPos.getX() - rectMin.getX();
        double rightDist = rectMax.getX() - pixelPos.getX();
        double topDist = pixelPos.getY() - rectMin.getY();
        double bottomDist = rectMax.getY() - pixelPos.getY();

        double minDist = std::min({ leftDist, rightDist, topDist, bottomDist });
        PhysicalPosition newPixelPos = pixelPos;

        if (minDist == leftDist) {
            newPixelPos.setX(rectMin.getX() - 1);  // Move pixel to the left of the rectangle
        }
        else if (minDist == rightDist) {
            newPixelPos.setX(rectMax.getX() + 1);  // Move pixel to the right of the rectangle
        }
        else if (minDist == topDist) {
            newPixelPos.setY(rectMin.getY() - 1);  // Move pixel to the top of the rectangle
        }
        else if (minDist == bottomDist) {
            newPixelPos.setY(rectMax.getY() + 1);  // Move pixel to the bottom of the rectangle
        }

        // Move the pixel out of the rectangle
        pixel->setPos(newPixelPos);

        // Apply forces to the pixel and the rectangle
        PhysicsVector pixelVelocity = pixel->getVelocity();
        PhysicsVector rectVelocity = rect->getVelocity();

        double pixelMass = pixel->getMass();
        double rectMass = rect->getMass();

        // Compute the relative velocity
        PhysicsVector relativeVelocity = pixelVelocity - rectVelocity;

        // Compute the collision normal (approximated by the minimum distance direction)
        PhysicsVector collisionNormal;
        if (minDist == leftDist) {
            collisionNormal = PhysicsVector(-1, 0);  // Moving left
        }
        else if (minDist == rightDist) {
            collisionNormal = PhysicsVector(1, 0);   // Moving right
        }
        else if (minDist == topDist) {
            collisionNormal = PhysicsVector(0, -1);  // Moving up
        }
        else if (minDist == bottomDist) {
            collisionNormal = PhysicsVector(0, 1);   // Moving down
        }

        // Compute the impulse scalar
        double restitution = 1.0;  // Elastic collision
        double impulseScalar = -(1 + restitution) * relativeVelocity.dot(collisionNormal);
        impulseScalar /= (1 / pixelMass + 1 / rectMass);

        // Compute the impulse vector
        PhysicsVector impulse = collisionNormal * impulseScalar;

        // Update velocities
        PhysicsVector newPixelVelocity = pixelVelocity + (impulse / pixelMass);
        PhysicsVector newRectVelocity = rectVelocity - (impulse / rectMass);

        // Apply new velocities
        pixel->setVelocity(newPixelVelocity * 0.75);
        rect->setVelocity(newRectVelocity * 0.75);

        // Compute the torque for the rectangle
        PhysicalPosition rectCenter = rect->getPos();
        PhysicsVector r = pixelPos - rectCenter;
        double torque = r.getX() * impulse.getY() - r.getY() * impulse.getX();  // Scalar cross product in 2D

        // Update the rectangle's angular velocity
        rect->addTorque(torque);

        return true;
    }

    return false;
}

bool Collision::handleCollision(PhysicsPixel* pixel1, PhysicsPixel* pixel2) {
	// since pixels are points whose coordinates are integers, we will cast both
	// components of the position to int and compare them that way
	// this is the only way in which pixles are diffrentf from points
	if ((int)pixel1->getPos().getX() == (int)pixel2->getPos().getX() && 
		(int)pixel1->getPos().getY() == (int)pixel2->getPos().getY()) {
		// move one of the pixels slightly to avoid division by zero
		pixel2->setPos(pixel2->getPos() + PhysicsVector(0.1, 0.1));

		PhysicsVector velocity1 = pixel1->getVelocity();
		PhysicsVector velocity2 = pixel2->getVelocity();

		// Swap velocities
		pixel1->setVelocity(velocity2);
		pixel2->setVelocity(velocity1);

		return true;
	}

	return false;
}

bool Collision::handleCollision(PhysicsRect* rect1, PhysicsRect* rect2) {
    bool hadCollision = false;

    auto [min1, max1] = rect1->getBoundingBox();
    auto [min2, max2] = rect2->getBoundingBox();

    // Check for overlap
    double overlapX = std::min(max1.getX(), max2.getX()) - std::max(min1.getX(), min2.getX());
    double overlapY = std::min(max1.getY(), max2.getY()) - std::max(min1.getY(), min2.getY());

    if (overlapX > 0 && overlapY > 0) {
        hadCollision = true;

        // Calculate the minimum overlap to resolve
        double overlap = std::min(overlapX, overlapY);

        // Resolve collision by moving objects apart
        PhysicalPosition pos1 = rect1->getPos();
        PhysicalPosition pos2 = rect2->getPos();
        PhysicsVector separationVector = pos1 - pos2;
        separationVector.normalize();

        // Move the objects apart by half the overlap each
        rect1->setPos(pos1 + separationVector * (overlap / 2));
        rect2->setPos(pos2 - separationVector * (overlap / 2));

        // Get the velocities and masses
        PhysicsVector velocity1 = rect1->getVelocity();
        PhysicsVector velocity2 = rect2->getVelocity();

        double mass1 = rect1->getMass();
        double mass2 = rect2->getMass();

        // Compute the relative velocity
        PhysicsVector relativeVelocity = velocity1 - velocity2;

        // Compute the collision normal (approximated by the separation vector)
        PhysicsVector collisionNormal = separationVector;

        // Compute the impulse scalar
        double restitution = 1.0;  // Elastic collision
        double impulseScalar = -(1 + restitution) * relativeVelocity.dot(collisionNormal);
        impulseScalar /= (1 / mass1 + 1 / mass2);

        // Compute the impulse vector
        PhysicsVector impulse = collisionNormal * impulseScalar;

        // Update linear velocities
        PhysicsVector newVelocity1 = velocity1 + (impulse / mass1);
        PhysicsVector newVelocity2 = velocity2 - (impulse / mass2);

        // Apply new linear velocities
        rect1->setVelocity(newVelocity1);
        rect2->setVelocity(newVelocity2);

        // Compute the torque for each rectangle
        PhysicalPosition center1 = rect1->getPos();
        PhysicalPosition center2 = rect2->getPos();
        PhysicsVector r1 = pos1 - center1;
        PhysicsVector r2 = pos2 - center2;

        const double torqueAmplificationFactor = 1e12;
        double torque1 = torqueAmplificationFactor * (r1.getX() * impulse.getY() - r1.getY() * impulse.getX());  // Scalar cross product in 2D
        double torque2 = torqueAmplificationFactor * (r2.getX() * impulse.getY() - r2.getY() * impulse.getX());  // Scalar cross product in 2D

        // Update the angular velocities
        rect1->addTorque(torque1);
        rect2->addTorque(torque2);
    }

    return hadCollision;
}