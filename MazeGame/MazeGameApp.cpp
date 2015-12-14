#include "MazeGameApp.h"
#include "MazeGrid.h"
#include "Player.h"

MazeGrid* mazeGrid;
Player* player;


void MazeGameApp::Initialize() {
	GameEngine::Initialize();

	mazeGrid = new MazeGrid(m_scene);

	player = new Player(m_mainCamera, mazeGrid);
	Add(player);
}

void MazeGameApp::Update(GameTime& gameTime) {
	//if (m_input->KeyPress(SDLK_w)) { // move up		
	//	if (mazeGrid->GridByIndex(camIndex - GRIDSIZE)->objectType != MazeObjectType::MAZE_WALL) {
	//		camIndex = camIndex - GRIDSIZE;
	//		camPos.z -= 2.0f;
	//	}
	//}

	//if (m_input->KeyPress(SDLK_s)) { // backward
	//	if (mazeGrid->GridByIndex(camIndex + GRIDSIZE)->objectType != MazeObjectType::MAZE_WALL) {
	//		camIndex = camIndex + GRIDSIZE;
	//		camPos.z += 2.0f;
	//	}
	//	//camPos -= camFront * camSpeed * gameTime.deltaTime;
	//}
	//
	//if (m_input->KeyPress(SDLK_a)) { // move left
	//	//camPos -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed * gameTime.deltaTime;
	//	if (mazeGrid->GridByIndex(camIndex - 1)->objectType != MazeObjectType::MAZE_WALL) {
	//		camIndex = camIndex - 1;
	//		camPos.x -= 2.0f;
	//	}
	//}
	//
	//if (m_input->KeyPress(SDLK_d)) { // move right
	//	//camPos += glm::normalize(glm::cross(camFront, camUp)) * camSpeed * gameTime.deltaTime;
	//	if (mazeGrid->GridByIndex(camIndex +1)->objectType != MazeObjectType::MAZE_WALL) {
	//		camIndex = camIndex +1;
	//		camPos.x += 2.0f;
	//	}
	//}

	m_scene->Update(gameTime);
}

void MazeGameApp::Render() {
	m_scene->Render(m_renderer);
}