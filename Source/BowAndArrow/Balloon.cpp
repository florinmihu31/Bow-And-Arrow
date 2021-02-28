#include "Balloon.h"

Balloon::Balloon(const std::string& name, glm::vec3 centerPoint, float radius, glm::vec3 colour,
	const std::string& stringName) {
	this->name = name;
	this->radius = radius;
	this->colour = colour;
	this->stringName = stringName;

	isHit = false;
	movesRight = rand() % 2 == 0;

	scale = 1.0f;
	scaleString = 1.0f;
	moveOffset = 0.0f;

	speedModifier = MIN_BALLOON_SPEED_MODIFIER + 
		(rand() % (MAX_BALLOON_SPEED_MODIFIER - MIN_BALLOON_SPEED_MODIFIER + 1));
}
