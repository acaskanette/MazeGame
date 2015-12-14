#include "MazeGameApp.h"
#include "MazeGrid.h"

#include <glm/gtx/rotate_vector.hpp>
#include <PointLight.h>

glm::vec3 camPos(0.0f, 1.0f, 15.0f);
glm::vec3 camFront(0.0f, 0.0f, -1.0f);
glm::vec3 camUp(0.0f, 1.0f, 0.0f);
GLfloat camRot = 0.0f;
GLfloat camSpeed = 50.0f;

MazeGrid* mazeGrid;
PointLight* light;

void MazeGameApp::Initialize() {
	GameEngine::Initialize();
	m_mainCamera->SetLocalPosition(camPos);

	mazeGrid = new MazeGrid(m_scene);
	light = new PointLight();
	light->SetLocalPosition(camPos);

	Add(light);
}

void MazeGameApp::Update(GameTime& gameTime) {
	if (m_input->KeyPress(SDLK_w)) { // forward
		camPos += camFront * camSpeed * gameTime.deltaTime;
	}
	if (m_input->KeyPress(SDLK_s)) { // backward
		camPos -= camFront * camSpeed * gameTime.deltaTime;
	}
	/*if (m_input->KeyPress(SDLK_a)) { // move left
		camPos -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed * gameTime.deltaTime;
	}
	if (m_input->KeyPress(SDLK_d)) { // move right
		camPos += glm::normalize(glm::cross(camFront, camUp)) * camSpeed * gameTime.deltaTime;
	}*/
	if (m_input->KeyDown(SDLK_q)) { // turn left
		camRot += camSpeed * gameTime.deltaTime;
		camFront = glm::rotate(glm::vec3(0, 0, -1), camRot, glm::vec3(0, 1, 0));
	}
	if (m_input->KeyDown(SDLK_e)) { // turn right
		camRot -= camSpeed * gameTime.deltaTime;
		camFront = glm::rotate(glm::vec3(0, 0, -1), camRot, glm::vec3(0, 1, 0));
	}

	m_mainCamera->SetLocalPosition(camPos);
	m_mainCamera->SetLookAt(camFront);
	light->SetLocalPosition(camPos + camFront);
	m_scene->Update(gameTime);
}

void MazeGameApp::Render() {
	m_scene->Render(m_renderer);
}