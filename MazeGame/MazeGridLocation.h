#pragma once
#include <GameObject.h>

enum MazeObjectType {
	MAZE_FLOOR, MAZE_WALL, MAZE_START, MAZE_END, MAZE_OBJECT1, MAZE_OBJECT2
};

class MazeGridLocation {
private:
	bool isPassable;			// whether this object can be passed through / you can move onto it
	GameObject* gameObject;		// The object that represents the grid location in the scene

public:
	MazeObjectType objectType;	// what type of object this is
	MazeGridLocation(MazeObjectType _objectType);
	MazeGridLocation(MazeObjectType _objectType, GameObject* gameMeshObject);
	
	void SetObjectType(MazeObjectType _objectType);
	void SetDefaultGameMesh();
	void SetGameObject(GameObject* _gameMeshObject);
	GameObject* GetGameObject();
};