#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include "windows.h"

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <GL/glew.h>

const unsigned short NUM_POINTS_BOW = 50;
const unsigned short NUM_TRIANGLES_BALLOON = 50;
const unsigned short NUM_BALLOONS = 15;
const unsigned short MIN_NUM_SHURIKENS = 2;
const unsigned short MAX_NUM_SHURIKENS = 5;

const unsigned int LEFT_MARGIN_OFFSET = 20;
const unsigned int BOTTOM_MARGIN_OFFSET = 10;
const unsigned int ROTATE_MODIFIER = 10;
const unsigned int LONG_PRESS_MILLISECONDS = 1500;
const unsigned int MEDIUM_PRESS_MILLISECONDS = 1000;
const unsigned int SHOT_LIMIT_MILLISECONDS = 2000;
const unsigned int MIN_BALLOON_SPEED_MODIFIER = 30;
const unsigned int MAX_BALLOON_SPEED_MODIFIER = 100;
const unsigned int MIN_SHURIKEN_SPEED_MODIFIER = 100;
const unsigned int MAX_SHURIKEN_SPEED_MODIFIER = 200;
const unsigned int MAX_NUM_LIVES = 3;

const float ARROW_LENGTH = 70.0f;
const float BOW_RADIUS = 50.0f;
const float BALLOON_RADIUS = 20.0f;
const float SHURIKEN_RADIUS = 30.0f;
const float BAR_LENGTH = 5.0f;
const float BAR_HEIGHT = 10.0f;
const float BALLOON_STRING_LENGTH = 30.0f;
const float TRANSLATE_MODIFIER = 100.0f;
const float DEFAULT_SPEED_MODIFIER = 300.0f;
const float COLLISION_ANIMATION_MODIFIER = 5.0f;
const float SCALE_BAR_MODIFIER = 10.0f;
const float MOVE_OFFSET_LIMIT = 20.0f;

const glm::vec3 RED = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 GREEN = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 BLUE = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 YELLOW = glm::vec3(1.0f, 1.0f, 0.0f);

const std::string ARROW_NAME = "arrow";
const std::string BOW_NAME = "bow";
const std::string BALLOON_NAME = "balloon";
const std::string BALLOON_STRING_NAME = "balloon_string";
const std::string SHURIKEN_NAME = "shuriken";
const std::string POWER_BAR_NAME = "power_bar";

Mesh* CreateArrow(const std::string& name, glm::vec3 headPoint, float length, glm::vec3 colour);
Mesh* CreateBow(const std::string& name, glm::vec3 centerPoint, float radius, glm::vec3 colour);
Mesh* CreateBalloon(const std::string& name, glm::vec3 centerPoint, float radius, glm::vec3 colour);
Mesh* CreateBalloonString(const std::string& name, glm::vec3 startPoint, glm::vec3 colour);
Mesh* CreateShuriken(const std::string& name, glm::vec3 centerPoint, float radius, glm::vec3 colour);
Mesh* CreatePowerBar(const std::string& name, glm::vec3 bottomLeftCorner, float length, float height, glm::vec3 colour);
void ShowScore(int score);
void ShowLives(unsigned int lives);