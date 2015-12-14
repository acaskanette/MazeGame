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
	m_scene->Update(gameTime);
}

void MazeGameApp::Render() {
	m_scene->Render(m_renderer);
}