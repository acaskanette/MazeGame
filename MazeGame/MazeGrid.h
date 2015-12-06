#pragma once

#include "MazeGridLocation.h"

#define GRIDSIZE 9

class MazeGrid {
	
private:	

	MazeGridLocation* mazeGrid[GRIDSIZE*GRIDSIZE];	

public:

	int startIndex;
	int finishIndex;
	GameObject* rootObject;
	MazeGridLocation* GridByIndex(int _index);

	MazeGrid(AbstractRenderer* _renderer);
	~MazeGrid();	

};