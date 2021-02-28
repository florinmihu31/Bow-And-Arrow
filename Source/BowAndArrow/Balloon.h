#pragma once

#include "BowAndArrow/Utils.h"

struct Balloon {
	Balloon(const std::string& name, glm::vec3 centerPoint, float radius, glm::vec3 colour,
		const std::string& stringName);

	std::string name, stringName;

	float translateX, translateY;
	float translateXString, translateYString;
	float scale, scaleString;
	float radius;
	float speedModifier;
	float moveOffset;
	
	glm::vec3 colour;
	
	bool isHit, movesRight;
};