#include "MazeGrid.h"

int grid[GRIDSIZE*GRIDSIZE] = {		// 0 = empty, 1 = wall, 2 = start, 3 = end, 4 = object1, 5 = object2

	1,3,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,5,1,
	1,1,1,1,1,1,0,1,1,
	1,0,0,0,1,1,0,0,1,
	1,0,1,0,0,0,0,0,1,
	1,0,1,0,1,1,1,0,1,
	1,0,1,0,1,0,1,0,1,
	1,0,1,4,1,0,0,0,1,
	2,0,1,1,1,1,1,1,1

};

MazeGrid::MazeGrid(AbstractRenderer* _renderer) {

	startIndex = -1;
	finishIndex = -1;

	rootObject = new GameObject();

	for (int i = 0; i < GRIDSIZE*GRIDSIZE; i++) {
		mazeGrid[i] = new MazeGridLocation((MazeObjectType)grid[i], _renderer);
		if ((MazeObjectType)grid[i] == MazeObjectType::MAZE_START)
			startIndex = i;
		if ((MazeObjectType)grid[i] == MazeObjectType::MAZE_END)
			finishIndex = i;
	}

}

MazeGrid::~MazeGrid() {

}


MazeGridLocation* MazeGrid::GridByIndex(int _index) {

	return mazeGrid[_index];
}
