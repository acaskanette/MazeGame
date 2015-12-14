#pragma once
#include <SceneGraph.h>
#include "MazeGridLocation.h"

#define GRIDSIZE 9

class MazeGrid {
private:	
	MazeGridLocation* mazeGrid[GRIDSIZE*GRIDSIZE];
	int startIndex;
	int finishIndex;
	GameObject* rootObject;

public:
	MazeGridLocation* GridByIndex(int _index);

	MazeGrid(SceneGraph* m_scene);
	~MazeGrid();	
};