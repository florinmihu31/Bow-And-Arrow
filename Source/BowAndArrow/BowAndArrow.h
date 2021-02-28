#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include "Balloon.h"
#include "Shuriken.h"

class BowAndArrow : public SimpleScene {
public:
	BowAndArrow();
	~BowAndArrow();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	glm::mat3 modelMatrix;
	
	float translateXArrow, translateYArrow;
	float scaleXArrow, scaleYArrow;
	float movingTranslateXArrow, movingTranslateYArrow, movingRotateArrow;
	float rotateArrow;

	float translateXBow, translateYBow;
	float scaleXBow, scaleYBow;
	float rotateBow;
	
	float translateXRedBar, translateYRedBar;
	float scaleBar;

	unsigned short clickHoldModifier;
	unsigned short balloonsNum, shurikensNum;

	unsigned int crtBalloon;
	unsigned int lives;

	int mouseX, mouseY;
	int score;

	bool isMovingArrow, isMousePressed;

	clock_t beginClick, currentClockMousePress, currentClockMovingArrow, arrowShoot;

	std::vector<Balloon> balloons;
	std::vector<Shuriken> shurikens;
};