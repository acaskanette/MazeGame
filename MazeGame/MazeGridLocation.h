#pragma once

#include "Cube2.h"
#include "Cube.h"
#include "FloorFace.h"
#include "FloorStart.h"
#include "FloorEnd.h"
#include "Wall.h"

enum MazeObjectType {
	MAZE_FLOOR, MAZE_WALL, MAZE_START, MAZE_END, MAZE_OBJECT1, MAZE_OBJECT2
};

class MazeGridLocation {

private:
	bool isPassable;			// whether this object can be passed through / you can move onto it
	MazeObjectType objectType;	// what type of object this is
	GameObject* gameMesh;		// The object that represents the grid location in the scene

public:

	MazeGridLocation(MazeObjectType _objectType, AbstractRenderer* _renderer);
	MazeGridLocation(MazeObjectType _objectType, GameObject* gameMeshObject, AbstractRenderer* _renderer);
	~MazeGridLocation();

	
	void SetObjectType(MazeObjectType _objectType);
	void SetDefaultGameMesh(AbstractRenderer* _renderer);
	void SetGameMesh(GameObject* _gameMeshObject);
	GameObject* GameMesh();

	void Render(AbstractRenderer* _renderer);

};
