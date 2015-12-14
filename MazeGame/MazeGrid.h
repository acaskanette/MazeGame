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

	int startIndex;
	int finishIndex;
	MazeGrid(SceneGraph* m_scene);
	~MazeGrid();	
};