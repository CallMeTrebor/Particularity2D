#ifndef GLOBAL_INFLUENCE_HPP
#define GLOBAL_INFLUENCE_HPP

#include "Influence.hpp"
#include "PhysicsObject.hpp"

class GlobalInfluence : public Influence {
public:
	GlobalInfluence() : GlobalInfluence(0.) {}
	GlobalInfluence(double magnitude) : Influence(magnitude) {}
};

#endif // !GLOBAL_INFLUENCE_HPP
