#include "MazeGameApp.h"
#include "MazeGrid.h"

#include <glm/gtx/rotate_vector.hpp>
#include <PointLight.h>

glm::vec3 camPos(0.0f, 1.0f, 15.0f);
glm::vec3 camFront(1.0f, 0.0f, 0.0f);
glm::vec3 camUp(0.0f, 1.0f, 0.0f);
GLfloat camRot = 0.0f;
GLfloat camSpeed = 50.0f;

int camIndex = 0;

MazeGrid* mazeGrid;
PointLight* light;

void MazeGameApp::Initialize() {
	GameEngine::Initialize();

	mazeGrid = new MazeGrid(m_scene);
	camIndex = mazeGrid->startIndex;
	camPos.x = -9.0f;
	camPos.y = 1.0f;
	camPos.z = 0.825f;

	m_mainCamera->SetLocalPosition(camPos);

	light = new PointLight();
	light->SetLocalPosition(camPos);

	Add(light);
}

void MazeGameApp::Update(GameTime& gameTime) {
	if (m_input->KeyPress(SDLK_w)) { // move up		
		if (mazeGrid->GridByIndex(camIndex - GRIDSIZE)->objectType != MazeObjectType::MAZE_WALL) {
			camIndex = camIndex - GRIDSIZE;
			camPos.z -= 2.0f;
		}
	}

	if (m_input->KeyPress(SDLK_s)) { // backward
		if (mazeGrid->GridByIndex(camIndex + GRIDSIZE)->objectType != MazeObjectType::MAZE_WALL) {
			camIndex = camIndex + GRIDSIZE;
			camPos.z += 2.0f;
		}
		//camPos -= camFront * camSpeed * gameTime.deltaTime;
	}
	
	if (m_input->KeyPress(SDLK_a)) { // move left
		//camPos -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed * gameTime.deltaTime;
		if (mazeGrid->GridByIndex(camIndex - 1)->objectType != MazeObjectType::MAZE_WALL) {
			camIndex = camIndex - 1;
			camPos.x -= 2.0f;
		}
	}
	
	if (m_input->KeyPress(SDLK_d)) { // move right
		//camPos += glm::normalize(glm::cross(camFront, camUp)) * camSpeed * gameTime.deltaTime;
		if (mazeGrid->GridByIndex(camIndex +1)->objectType != MazeObjectType::MAZE_WALL) {
			camIndex = camIndex +1;
			camPos.x += 2.0f;
		}
	}

	if (m_input->KeyPress(SDLK_q)) { // turn left
		camRot += 90.f;
		camFront = glm::rotate(glm::vec3(0, 0, -1), camRot, glm::vec3(0, 1, 0));
	}
	if (m_input->KeyPress(SDLK_e)) { // turn right
		camRot -= 90.f;
		camFront = glm::rotate(glm::vec3(0, 0, -1), camRot, glm::vec3(0, 1, 0));
	}

	m_mainCamera->SetLocalPosition(camPos);
	printf("%f\n",camPos.x);
	m_mainCamera->SetLookAt(camFront);
	light->SetLocalPosition(camPos + camFront);
	m_scene->Update(gameTime);
}

void MazeGameApp::Render() {
	m_scene->Render(m_renderer);
}