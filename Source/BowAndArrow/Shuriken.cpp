#include "Shuriken.h"

Shuriken::Shuriken(const std::string& name, glm::vec3 centerPoint, float radius, glm::vec3 colour) {
	this->name = name;
	this->radius = radius;
	this->colour = colour;

	isHit = false;
	hitPlayer = false;

	scale = 1.0f;
	rotate = 0.0f;

	speedModifier = MIN_SHURIKEN_SPEED_MODIFIER +
		(rand() % (MAX_SHURIKEN_SPEED_MODIFIER - MIN_SHURIKEN_SPEED_MODIFIER + 1));
}
