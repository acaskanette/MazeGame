#include "Player.h"
#include <InputManager.h>
#include <glm/gtx/rotate_vector.hpp>

Player::Player(Camera* mainCamera, MazeGrid* theGrid) : turnSpeed(50.0f), currentRotation(0.0f) {
	camera = mainCamera;
	mazeGrid = theGrid;

	currentGridIndex = mazeGrid->startIndex;

	light = new PointLight();
	AddChild(light);
	light->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
	light->SetAmbient(glm::vec3(0.1f, 0.05f, 0.05f));
	light->SetDiffuse(glm::vec3(0.25f, 0.1f, 0.1f));

	SetLocalPosition(glm::vec3(-9.0f, 1.0f, 0.825f));
	camera->SetLocalPosition(GetLocalPosition());
	camera->SetForward(glm::vec3(1.0f, 0.0f, 0.0f));
}

void Player::UpdateMe(GameTime& gameTime) {
	if (InputManager::GetInstance()->KeyDown(SDLK_q)) { // turn left
		currentRotation += turnSpeed * gameTime.deltaTime;
		camera->SetForward(glm::rotate(glm::vec3(1, 0, 0), currentRotation, glm::vec3(0, 1, 0)));
	} else if (InputManager::GetInstance()->KeyDown(SDLK_e)) { // turn right
		currentRotation -= turnSpeed * gameTime.deltaTime;
		camera->SetForward(glm::rotate(glm::vec3(1, 0, 0), currentRotation, glm::vec3(0, 1, 0)));
	}

	if (InputManager::GetInstance()->KeyPress(SDLK_w)) // move forward
		Move(camera->GetForward());
	else if (InputManager::GetInstance()->KeyPress(SDLK_s)) // move backward
		Move(-camera->GetForward());
	else if (InputManager::GetInstance()->KeyPress(SDLK_a)) // move left
		Move(-camera->GetRight());
	else if (InputManager::GetInstance()->KeyPress(SDLK_d)) // move right
		Move(camera->GetRight());

	camera->SetLocalPosition(GetLocalPosition());
}

void Player::Move(glm::vec3 direction) {
	int moveIndex = GetGridIndexFromDirection(direction);
	if (moveIndex == -1 || mazeGrid->GridByIndex(moveIndex)->objectType == MazeObjectType::MAZE_WALL || mazeGrid->GridByIndex(moveIndex)->objectType == MazeObjectType::MAZE_OBJECT1) {
		printf("Can't move there!");
		return;
	}

	currentGridIndex = moveIndex;

	//Unlock door
	if (mazeGrid->GridByIndex(currentGridIndex)->objectType == MazeObjectType::MAZE_OBJECT2)
		mazeGrid->UnlockDoor();

	// Winner!
	if (mazeGrid->GridByIndex(currentGridIndex)->objectType == MazeObjectType::MAZE_END) {
		light->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
		light->SetAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
		light->SetDiffuse(glm::vec3(0.1f, 0.1f, 0.1f));
	}


	m_position += direction * 2.0f;
}

int Player::GetGridIndexFromDirection(glm::vec3& direction) {
	float x = direction.x;
	float z = direction.z;

	// up z on grid (north)
	if ((x >= -0.5f && x <= 0.5f) && z <= -0.85f) {
		direction = glm::vec3(0, 0, -1); // modify reference to direction to ensure positioning on grid center
		return currentGridIndex - GRIDSIZE;
	} // down z on grid (south)
	else if ((x >= -0.5f && x <= 0.5f) && z >= 0.85f) {
		direction = glm::vec3(0, 0, 1);
		return currentGridIndex + GRIDSIZE;
	} // down on x grid (west)
	else if ((z >= -0.5f && z <= 0.5f) && x <= -0.85f) {
		direction = glm::vec3(-1, 0, 0);
		return currentGridIndex - 1;
	} // up on x grid (east)
	else if ((z >= -0.5f && z <= 0.5f) && x >= 0.85f) {
		direction = glm::vec3(1, 0, 0);
		return currentGridIndex + 1;
	} // diagonal or not a grid position
	else 
		return -1;
}