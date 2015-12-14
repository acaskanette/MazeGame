#include "MazeGameApp.h"
#include "MazeGrid.h"

#include <glm/gtx/rotate_vector.hpp>
#include <PointLight.h>

glm::vec3 camPos(0.0f, 1.0f, 15.0f);
glm::vec3 camLook(0.0f, 0.0f, 0.0f);
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
		camPos.z -= camSpeed * gameTime.deltaTime;
		camLook.z -= camSpeed * gameTime.deltaTime;
	}
	if (m_input->KeyPress(SDLK_s)) { // backward
		camPos.z += camSpeed * gameTime.deltaTime;
		camLook.z += camSpeed * gameTime.deltaTime;
	}
	if (m_input->KeyPress(SDLK_a)) { // move left
		camPos.x -= camSpeed * gameTime.deltaTime;
		camLook.x -= camSpeed * gameTime.deltaTime;
	}
	if (m_input->KeyPress(SDLK_d)) { // move right
		camPos.x += camSpeed * gameTime.deltaTime;
		camLook.x += camSpeed * gameTime.deltaTime;
	}
	if (m_input->KeyPress(SDLK_q)) { // turn left
		camLook = glm::rotate(camLook, -45.0f, glm::vec3(0, 1, 0));
	}
	if (m_input->KeyPress(SDLK_e)) { // turn right
		camLook = glm::rotate(camLook, 45.0f, glm::vec3(0, 1, 0));
	}

	m_mainCamera->SetLocalPosition(camPos);
	m_mainCamera->SetLookAt(camLook);
	light->SetLocalPosition(camPos);
	m_scene->Update(gameTime);
}

void MazeGameApp::Render() {
	m_scene->Render(m_renderer);
}