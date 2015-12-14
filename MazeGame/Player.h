#pragma once
#include <GameObject.h>
#include <Camera.h>
#include <PointLight.h>
#include "MazeGrid.h"

class Player : public GameObject {
public:
	virtual void UpdateMe(GameTime& gameTime) override;
	void Move(glm::vec3 direction);

	Player(Camera* mainCamera, MazeGrid* theGrid);
private:
	Camera* camera;
	PointLight* light;

	MazeGrid* mazeGrid;
	int currentGridIndex;

	float turnSpeed;
	float currentRotation;

	int GetGridIndexFromDirection(glm::vec3& direction);
};