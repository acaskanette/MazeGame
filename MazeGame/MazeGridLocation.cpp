#include "MazeGridLocation.h"
#include "Cube.h"

MazeGridLocation::MazeGridLocation(MazeObjectType _objectType) {
	SetObjectType(_objectType);
	SetDefaultGameMesh();	
}

MazeGridLocation::MazeGridLocation(MazeObjectType _objectType, GameObject* _gameMeshObject) {
	SetObjectType(_objectType);
	SetGameObject(_gameMeshObject);
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

void MazeGridLocation::SetDefaultGameMesh() {
	switch (objectType) {
	case MAZE_WALL:
	case MAZE_FLOOR:
	case MAZE_OBJECT1:
	case MAZE_OBJECT2:
		gameObject = new Cube("models/crate/crate.obj");
		break;
	case MAZE_START:
		gameObject = new Cube("models/crateStart/crate.obj");
		break;
	case MAZE_END:
		gameObject = new Cube("models/crateFinish/crate.obj");
		break;
	
	default:
		break;
	}
}

void MazeGridLocation::SetGameObject(GameObject* _gameMeshObject) {
	gameObject = _gameMeshObject;
}

GameObject* MazeGridLocation::GetGameObject() {
	return gameObject;
}