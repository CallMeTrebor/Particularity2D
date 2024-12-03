#ifndef LOCAL_INFLUENCE_HPP
#define LOCAL_INFLUENCE_HPP

#include "Influence.hpp"
#include "PhysicsProps.hpp"
#include "PhysicsObject.hpp"

class LocalInfluence : public Influence {
protected:
	PhysicalPosition sourcePosition;
public:
	LocalInfluence() : sourcePosition(PhysicalPosition(0, 0)), Influence(0) {}
	LocalInfluence(PhysicalPosition sourcePosition, double magnitude) : sourcePosition(sourcePosition), Influence(magnitude) {}

	PhysicalPosition getSourcePosition() const { return sourcePosition; }
	void setSourcePosition(PhysicalPosition sourcePosition) { this->sourcePosition = sourcePosition; }
};

#endif // !LOCAL_INFLUENCE_HPP
