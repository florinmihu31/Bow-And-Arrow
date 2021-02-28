#pragma once

#include "BowAndArrow/Utils.h"

struct Shuriken {
	Shuriken(const std::string& name, glm::vec3 centerPoint, float radius, glm::vec3 colour);

	std::string name;

	float translateX, translateY;
	float radius;
	float scale;
	float speedModifier;
	float rotate;
	
	glm::vec3 colour;
	
	bool isHit, hitPlayer;
};