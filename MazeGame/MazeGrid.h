#pragma once
#include <SceneGraph.h>
#include "MazeGridLocation.h"

#define GRIDSIZE 11

class MazeGrid {
private:	
	MazeGridLocation* mazeGrid[GRIDSIZE*GRIDSIZE];
	GameObject* rootObject;

public:
	MazeGridLocation* GridByIndex(int _index);
	void UnlockDoor();

	int startIndex;
	int finishIndex;
	int doorIndex;
	MazeGrid(SceneGraph* m_scene);
	~MazeGrid();	
};