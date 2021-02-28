#include "BowAndArrow.h"
#include "Transform2D.h"

BowAndArrow::BowAndArrow() {
}

BowAndArrow::~BowAndArrow() {
}

void BowAndArrow::Init() {
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// Initializarea sageata
	Mesh* arrow = CreateArrow(ARROW_NAME, glm::vec3(0.0f, 0.0f, 0.0f), ARROW_LENGTH, GREEN);
	AddMeshToList(arrow);

	// Initializarea arc
	Mesh* bow = CreateBow(BOW_NAME, glm::vec3(0.0f, 0.0f, 0.0f), BOW_RADIUS, GREEN);
	AddMeshToList(bow);

	// Initializare power bar
	Mesh* powerBar = CreatePowerBar(POWER_BAR_NAME, glm::vec3(0.0f, 0.0f, 0.0f),
		BAR_LENGTH, BAR_HEIGHT, GREEN);
	AddMeshToList(powerBar);

	// Initializare coordonate de translatie
	translateXArrow = LEFT_MARGIN_OFFSET + ARROW_LENGTH;
	translateYArrow = resolution.y / 2;

	translateXBow = LEFT_MARGIN_OFFSET;
	translateYBow = resolution.y / 2;

	// Initializare unghi de rotatie
	rotateArrow = 0;
	rotateBow = 0;

	// Initializare scalare power bar
	scaleBar = 1.0f;

	// Initializare variabile booleane
	isMousePressed = false;
	isMovingArrow = false;

	// Generare numere aleatoare
	srand((unsigned)time(NULL));
	shurikensNum = MIN_NUM_SHURIKENS + (rand() % (MAX_NUM_SHURIKENS - MIN_NUM_SHURIKENS + 1));

	// Initializare numar balon curent
	crtBalloon = 0;

	// Initializare scor si numar de vieti
	score = 0;
	lives = MAX_NUM_LIVES;

	// Afisare scor si vieti initiale
	ShowScore(score);
	ShowLives(lives);

	// Initializarea vector de baloane
	for (size_t i = 0; i < NUM_BALLOONS; ++i, ++crtBalloon) {
		std::string name = BALLOON_NAME + std::to_string(i);
		std::string stringName = BALLOON_STRING_NAME + std::to_string(i);
		glm::vec3 centerPoint = glm::vec3(0.0f, 0.0f, 0.0f);
		float radius = BALLOON_RADIUS;
		glm::vec3 colour = (rand() % 2 == 0) ? RED : YELLOW;

		balloons.emplace_back(name, centerPoint, radius, colour, stringName);
		balloons[i].translateX = resolution.x / 2 + (rand() % (resolution.x / 2 + 1));
		balloons[i].translateY = -1.5f * radius;
		balloons[i].translateXString = balloons[i].translateX;
		balloons[i].translateYString = balloons[i].translateY - 1.5f * radius;

		Mesh* balloon = CreateBalloon(name, centerPoint, radius, colour);
		AddMeshToList(balloon);

		Mesh* balloonString = CreateBalloonString(stringName, glm::vec3(0, 0, 0), colour);
		AddMeshToList(balloonString);
	}

	// Initializare vector de shurikenuri
	for (size_t i = 0; i < shurikensNum; ++i) {
		std::string name = SHURIKEN_NAME + std::to_string(i);
		glm::vec3 centerPoint = glm::vec3(0.0f, 0.0f, 0.0f);
		float radius = SHURIKEN_RADIUS;
		glm::vec3 colour = BLUE;

		shurikens.emplace_back(name, centerPoint, radius, colour);
		shurikens[i].translateX = resolution.x + radius;
		shurikens[i].translateY = radius + (rand() % (resolution.y - 2 * (int)radius + 1));

		Mesh* shuriken = CreateShuriken(name, centerPoint, radius, colour);
		AddMeshToList(shuriken);
	}
}

void BowAndArrow::FrameStart() {
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void BowAndArrow::Update(float deltaTimeSeconds) {
	glm::ivec2 resolution = window->GetResolution();

	// Arrow + Bow
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXArrow, translateYArrow);
	modelMatrix *= Transform2D::Rotate(rotateArrow);

	if (!isMovingArrow) {
		RenderMesh2D(meshes[ARROW_NAME], shaders["VertexColor"], modelMatrix);
	}

	translateXBow = translateXArrow - 2 * ARROW_LENGTH - LEFT_MARGIN_OFFSET;
	translateYBow = translateYArrow;
	float bowX = translateXArrow - ARROW_LENGTH * cos(rotateArrow);
	float bowY = translateYArrow - ARROW_LENGTH * sin(rotateArrow);

	modelMatrix *= Transform2D::Translate(translateXBow, 0);
	RenderMesh2D(meshes[BOW_NAME], shaders["VertexColor"], modelMatrix);

	for (size_t i = 0; i < balloons.size(); ++i) {
		if (balloons[i].scale > 0.0f) {
			if (balloons[i].isHit) {
				balloons[i].scale -= deltaTimeSeconds * COLLISION_ANIMATION_MODIFIER;
				balloons[i].scaleString -= deltaTimeSeconds * COLLISION_ANIMATION_MODIFIER;

				if (balloons[i].scale < 0.0f) {
					balloons[i].isHit = false;
				}
			}

			if (balloons[i].movesRight) {
				balloons[i].moveOffset += deltaTimeSeconds * balloons[i].speedModifier / 2;

				if (balloons[i].moveOffset > MOVE_OFFSET_LIMIT) {
					balloons[i].movesRight = false;
				}
			} else {
				balloons[i].moveOffset -= deltaTimeSeconds * balloons[i].speedModifier / 2;

				if (balloons[i].moveOffset < -MOVE_OFFSET_LIMIT) {
					balloons[i].movesRight = true;
				}
			}

			balloons[i].translateY += deltaTimeSeconds * balloons[i].speedModifier;
			balloons[i].translateYString += deltaTimeSeconds * balloons[i].speedModifier;

			// Randare balon
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(balloons[i].translateX + balloons[i].moveOffset,
				balloons[i].translateY);
			modelMatrix *= Transform2D::Scale(balloons[i].scale, balloons[i].scale);
			RenderMesh2D(meshes[balloons[i].name], shaders["VertexColor"], modelMatrix);

			// Randare ata balon
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(balloons[i].translateXString + balloons[i].moveOffset,
				balloons[i].translateYString);
			modelMatrix *= Transform2D::Scale(balloons[i].scaleString, balloons[i].scaleString);
			RenderMesh2D(meshes[balloons[i].stringName], shaders["VertexColor"], modelMatrix);

			if (balloons[i].scale < 0.0f ||
				balloons[i].translateYString - BALLOON_STRING_LENGTH > resolution.y) {
				balloons.erase(balloons.begin() + i);
			}
		}
	}

	// Adaugare balon nou
	if (balloons.size() < NUM_BALLOONS) {
		std::string name = BALLOON_NAME + std::to_string(crtBalloon);
		std::string stringName = BALLOON_STRING_NAME + std::to_string(crtBalloon++);
		glm::vec3 centerPoint = glm::vec3(0.0f, 0.0f, 0.0f);
		float radius = BALLOON_RADIUS;
		glm::vec3 colour = (rand() % 2 == 0) ? RED : YELLOW;

		balloons.emplace_back(name, centerPoint, radius, colour, stringName);
		balloons[balloons.size() - 1].translateX = resolution.x / 2 + (rand() % (resolution.x / 2 + 1));
		balloons[balloons.size() - 1].translateY = 0.0f;
		balloons[balloons.size() - 1].translateXString = balloons[balloons.size() - 1].translateX;
		balloons[balloons.size() - 1].translateYString = balloons[balloons.size() - 1].translateY - 1.5f * radius;

		Mesh* balloon = CreateBalloon(name, centerPoint, radius, colour);
		AddMeshToList(balloon);

		Mesh* balloonString = CreateBalloonString(stringName, glm::vec3(0, 0, 0), colour);
		AddMeshToList(balloonString);
	}

	// Randare shurikenuri
	for (size_t i = 0; i < shurikens.size(); ++i) {
		if (shurikens[i].scale > 0.0f) {
			if (shurikens[i].isHit) {
				shurikens[i].scale -= deltaTimeSeconds * COLLISION_ANIMATION_MODIFIER;

				if (shurikens[i].scale < 0.0f) {
					shurikens[i].isHit = false;
				}
			}

			if (!shurikens[i].isHit) {
				shurikens[i].translateX -= deltaTimeSeconds * shurikens[i].speedModifier;
			}

			shurikens[i].rotate += deltaTimeSeconds * ROTATE_MODIFIER;

			// Randare shuriken
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(shurikens[i].translateX, shurikens[i].translateY);
			modelMatrix *= Transform2D::Rotate(shurikens[i].rotate);
			modelMatrix *= Transform2D::Scale(shurikens[i].scale, shurikens[i].scale);

			RenderMesh2D(meshes[shurikens[i].name], shaders["VertexColor"], modelMatrix);
		}

		if (shurikens[i].translateX < -shurikens[i].radius || shurikens[i].scale < 0.0f) {
			shurikens.erase(shurikens.begin() + i);
		}
	}

	if (shurikens.size() == 0) {
		shurikensNum = MIN_NUM_SHURIKENS + (rand() % (MAX_NUM_SHURIKENS - MIN_NUM_SHURIKENS + 1));

		for (size_t i = 0; i < shurikensNum; ++i) {
			std::string name = SHURIKEN_NAME + std::to_string(i);
			glm::vec3 centerPoint = glm::vec3(0.0f, 0.0f, 0.0f);
			float radius = SHURIKEN_RADIUS;
			glm::vec3 colour = BLUE;

			shurikens.emplace_back(name, centerPoint, radius, colour);
			shurikens[i].translateX = resolution.x + radius;
			shurikens[i].translateY = radius + (rand() % (resolution.y - 2 * (int)radius + 1));

			Mesh* shuriken = CreateShuriken(name, centerPoint, radius, colour);
			AddMeshToList(shuriken);
		}
	}

	if (isMousePressed) {
		currentClockMousePress = clock();

		translateXRedBar = bowX;
		translateYRedBar = bowY - BOW_RADIUS - BAR_HEIGHT - 5;
		if (scaleBar < 10.0f) {
			scaleBar += deltaTimeSeconds * SCALE_BAR_MODIFIER;
		}

		// PowerBar
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translateXRedBar, translateYRedBar);
		modelMatrix *= Transform2D::Scale(scaleBar, 1.0f);
		RenderMesh2D(meshes[POWER_BAR_NAME], shaders["VertexColor"], modelMatrix);
	} else if (!isMovingArrow) {
		scaleBar = 1.0f;
	}

	if (isMovingArrow) {
		currentClockMovingArrow = clock();

		if (scaleBar > 9.0f) {
			clickHoldModifier = 3;
		} else if (scaleBar > 6.0f) {
			clickHoldModifier = 2;
		} else {
			clickHoldModifier = 1;
		}

		movingTranslateXArrow += deltaTimeSeconds * DEFAULT_SPEED_MODIFIER
			* clickHoldModifier * cos(movingRotateArrow);
		movingTranslateYArrow += deltaTimeSeconds * DEFAULT_SPEED_MODIFIER
			* clickHoldModifier * sin(movingRotateArrow);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(movingTranslateXArrow, movingTranslateYArrow);
		modelMatrix *= Transform2D::Rotate(movingRotateArrow);
		RenderMesh2D(meshes[ARROW_NAME], shaders["VertexColor"], modelMatrix);

		// Coliziune sageata-balon
		for (Balloon& balloon : balloons) {
			float ellipseDx = (movingTranslateXArrow - balloon.translateX) *
				(movingTranslateXArrow - balloon.translateX);
			float ellipseDy = (movingTranslateYArrow - balloon.translateY) *
				(movingTranslateYArrow - balloon.translateY);
			float ellipseDistance = (ellipseDx / (balloon.radius * balloon.radius)) +
				(ellipseDy / (1.5f * balloon.radius * 1.5f * balloon.radius));

			if (ellipseDistance <= 1 && !balloon.isHit) {
				balloon.isHit = true;

				if (balloon.colour == RED) {
					ShowScore(++score);
				} else {
					ShowScore(--score);
				}
			}
		}

		if (movingTranslateXArrow > resolution.x + ARROW_LENGTH ||
			currentClockMovingArrow - arrowShoot > SHOT_LIMIT_MILLISECONDS) {
			isMovingArrow = false;
		}

		// Coliziune sageata-shuriken
		for (Shuriken& shuriken : shurikens) {
			float dx = movingTranslateXArrow - shuriken.translateX;
			float dy = movingTranslateYArrow - shuriken.translateY;
			float distance = sqrt(dx * dx + dy * dy);

			if (distance < SHURIKEN_RADIUS) {
				shuriken.isHit = true;
				ShowScore(++score);
				isMovingArrow = false;
			}
		}
	}

	// Coliziune shuriken-jucator
	for (Shuriken& shuriken : shurikens) {
		float dx = bowX - shuriken.translateX;
		float dy = bowY - shuriken.translateY;
		float distance = sqrt(dx * dx + dy * dy);

		if (distance < BOW_RADIUS + shuriken.radius && !shuriken.isHit) {
			shuriken.isHit = true;
			ShowLives(--lives);
		}

		if (lives == 0) {
			std::cout << "Game Over\n";
			exit(EXIT_SUCCESS);
		}
	}
}

void BowAndArrow::FrameEnd() {
}

void BowAndArrow::OnInputUpdate(float deltaTime, int mods) {
	glm::ivec2 resolution = window->GetResolution();

	if (window->KeyHold(GLFW_KEY_W) && translateYArrow < resolution.y && translateYBow < resolution.y) {
		translateYArrow += TRANSLATE_MODIFIER * deltaTime;
		translateYBow += TRANSLATE_MODIFIER * deltaTime;
		rotateArrow = rotateBow = atan((resolution.y - mouseY - translateYArrow) / (mouseX - translateXArrow));
	}

	if (window->KeyHold(GLFW_KEY_S) && translateYArrow > 0 && translateYBow > 0) {
		translateYArrow -= TRANSLATE_MODIFIER * deltaTime;
		translateYBow -= TRANSLATE_MODIFIER * deltaTime;
		rotateArrow = rotateBow = atan((resolution.y - mouseY - translateYArrow) / (mouseX - translateXArrow));
	}
}

void BowAndArrow::OnKeyPress(int key, int mods) {
}

void BowAndArrow::OnKeyRelease(int key, int mods) {
}

void BowAndArrow::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
	glm::ivec2 resolution = window->GetResolution();

	this->mouseX = mouseX;
	this->mouseY = mouseY;

	rotateArrow = rotateBow = atan((resolution.y - mouseY - translateYArrow) / (mouseX - translateXArrow));
}

void BowAndArrow::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
	if (button == 1 && !isMovingArrow) {
		beginClick = clock();
		isMousePressed = true;
	}
}

void BowAndArrow::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
	if (button == 1 && !isMovingArrow) {
		arrowShoot = clock();
		isMovingArrow = true;
		isMousePressed = false;
		movingRotateArrow = rotateArrow;
		movingTranslateXArrow = translateXArrow;
		movingTranslateYArrow = translateYArrow;
	}
}

void BowAndArrow::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
}

void BowAndArrow::OnWindowResize(int width, int height) {
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);
}
