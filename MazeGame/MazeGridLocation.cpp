#include "MazeGridLocation.h"

MazeGridLocation::MazeGridLocation(MazeObjectType _objectType, AbstractRenderer* _renderer) {
	
	SetObjectType(_objectType);
	SetDefaultGameMesh(_renderer);	

}

MazeGridLocation::MazeGridLocation(MazeObjectType _objectType, GameObject* _gameMeshObject, AbstractRenderer* _renderer) {

	SetObjectType(_objectType);
	SetGameMesh(_gameMeshObject);

}


MazeGridLocation::~MazeGridLocation() { 
	
	delete gameMesh; 

}

void MazeGridLocation::SetObjectType(MazeObjectType _objectType) {

	objectType = _objectType;

	switch (objectType) {
	case MAZE_WALL:
		isPassable = false;
		break;
	case MAZE_START:
	case MAZE_END:
	case MAZE_FLOOR:
	case MAZE_OBJECT1:
	case MAZE_OBJECT2:
		isPassable = true;
		break;
	default:
		isPassable = false;

	}

}

void MazeGridLocation::SetDefaultGameMesh(AbstractRenderer* _renderer) {

	switch (objectType) {
	case MAZE_WALL:
		gameMesh = new Cube(_renderer);
		break;
	case MAZE_START:
	case MAZE_END:
	case MAZE_FLOOR:
	case MAZE_OBJECT1:
	case MAZE_OBJECT2:
	default:
		break;
	}

	

}

void MazeGridLocation::SetGameMesh(GameObject* _gameMeshObject) {

	gameMesh = _gameMeshObject;

}

GameObject* MazeGridLocation::GameMesh() {

	return gameMesh;

}

void MazeGridLocation::Render(AbstractRenderer* _renderer) {
//	gameMesh->Render(_renderer);
}