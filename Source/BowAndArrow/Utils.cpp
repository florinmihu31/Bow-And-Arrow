#include "BowAndArrow/Utils.h"

Mesh* CreateArrow(const std::string& name, glm::vec3 headPoint, float length, glm::vec3 colour) {
	std::vector<VertexFormat> verticesArrow = {
		VertexFormat(headPoint, colour),
		VertexFormat(headPoint + glm::vec3(-10, 10, 0), colour),
		VertexFormat(headPoint + glm::vec3(-10, -10, 0), colour),
		VertexFormat(headPoint + glm::vec3(-10, 0, 0), colour),
		VertexFormat(headPoint + glm::vec3(-length, 0, 0), colour),
	};

	std::vector<unsigned short> indicesArrow = {
		0, 1,
		0, 2,
		1, 2,
		3, 4
	};

	Mesh* arrow = new Mesh(name);
	arrow->SetDrawMode(GL_LINES);
	arrow->InitFromData(verticesArrow, indicesArrow);

	return arrow;
}

Mesh* CreateBow(const std::string& name, glm::vec3 centerPoint, float radius, glm::vec3 colour) {
	std::vector<VertexFormat> verticesBow;
	std::vector<unsigned short> indicesBow;

	for (unsigned short i = 0; i <= NUM_POINTS_BOW; ++i) {
		float position = M_PI * i / NUM_POINTS_BOW;

		verticesBow.emplace_back(centerPoint + glm::vec3(radius * sin(position), radius * cos(position), 0), colour);
		indicesBow.emplace_back(i);
	}

	Mesh* bow = new Mesh(name);
	bow->SetDrawMode(GL_LINE_LOOP);
	bow->InitFromData(verticesBow, indicesBow);

	return bow;
}

Mesh* CreateBalloon(const std::string& name, glm::vec3 centerPoint, float radius, glm::vec3 colour) {
	std::vector<VertexFormat> verticesBalloon = { VertexFormat(centerPoint, colour) };
	std::vector<unsigned short> indicesBalloon;

	for (unsigned short i = 0; i < NUM_TRIANGLES_BALLOON; ++i) {
		float position = 2 * M_PI * i / NUM_TRIANGLES_BALLOON;

		verticesBalloon.emplace_back(
			centerPoint + glm::vec3(radius * cos(position), 1.5f * radius * sin(position), 0),
			colour
		);

		indicesBalloon.emplace_back(i);
	}

	indicesBalloon.emplace_back(NUM_TRIANGLES_BALLOON);
	indicesBalloon.emplace_back(1);

	Mesh* balloon = new Mesh(name);
	balloon->SetDrawMode(GL_TRIANGLE_FAN);
	balloon->InitFromData(verticesBalloon, indicesBalloon);

	return balloon;
}

Mesh* CreateBalloonString(const std::string& name, glm::vec3 startPoint, glm::vec3 colour) {
	std::vector<VertexFormat> verticesBalloonString = {
		VertexFormat(startPoint, colour),
		VertexFormat(startPoint + glm::vec3(-5, -10, 0), colour),
		VertexFormat(startPoint + glm::vec3(5, -20, 0), colour),
		VertexFormat(startPoint + glm::vec3(0, -30, 0), colour)
	};

	std::vector<unsigned short> indicesBalloonString = { 0, 1, 2, 3 };

	Mesh* balloonString = new Mesh(name);
	balloonString->SetDrawMode(GL_LINE_STRIP);
	balloonString->InitFromData(verticesBalloonString, indicesBalloonString);

	return balloonString;
}

Mesh* CreateShuriken(const std::string& name, glm::vec3 centerPoint, float radius, glm::vec3 colour) {
	std::vector<VertexFormat> verticesShuriken = {
		VertexFormat(centerPoint, colour),
		VertexFormat(centerPoint + glm::vec3(radius, 0, 0), colour),
		VertexFormat(centerPoint + glm::vec3(radius, radius, 0), colour),
		VertexFormat(centerPoint + glm::vec3(0, radius, 0), colour),
		VertexFormat(centerPoint + glm::vec3(-radius, radius, 0), colour),
		VertexFormat(centerPoint + glm::vec3(-radius, 0, 0), colour),
		VertexFormat(centerPoint + glm::vec3(-radius, -radius, 0), colour),
		VertexFormat(centerPoint + glm::vec3(0, -radius, 0), colour),
		VertexFormat(centerPoint + glm::vec3(radius, -radius, 0), colour),
	};

	std::vector<unsigned short> indicesShuriken = {
		0, 1, 2,
		0, 3, 4,
		0, 5, 6,
		0, 7, 8
	};

	Mesh* shuriken = new Mesh(name);
	shuriken->SetDrawMode(GL_TRIANGLES);
	shuriken->InitFromData(verticesShuriken, indicesShuriken);

	return shuriken;
}

Mesh* CreatePowerBar(const std::string& name, glm::vec3 bottomLeftCorner, float length, float height, glm::vec3 colour) {
	std::vector<VertexFormat> verticesPowerBar = {
		VertexFormat(bottomLeftCorner, colour),
		VertexFormat(bottomLeftCorner + glm::vec3(0, height, 0), colour),
		VertexFormat(bottomLeftCorner + glm::vec3(length, height, 0), colour),
		VertexFormat(bottomLeftCorner + glm::vec3(length, 0, 0), colour)
	};

	std::vector<unsigned short> indicesPowerBar = {
		0, 1, 2,
		0, 2, 3
	};

	Mesh* powerBar = new Mesh(name);
	powerBar->SetDrawMode(GL_TRIANGLES);
	powerBar->InitFromData(verticesPowerBar, indicesPowerBar);

	return powerBar;
}

void ShowScore(int score) {
	std::cout << "Score: " << score << "\n";
}

void ShowLives(unsigned int lives) {
	std::cout << "Lives left: " << lives << "\n";
}
