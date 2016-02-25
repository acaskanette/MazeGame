#include "MazeGrid.h"
#include "DoorObject.h"

int grid[GRIDSIZE*GRIDSIZE] = {		// 0 = empty, 1 = wall, 2 = start, 3 = end, 4 = object1(door), 5 = object2(key)
	1,1,1,1,1,1,1,1,1,1,1,
	1,1,3,1,1,1,1,1,1,1,1,
	1,1,0,0,0,0,0,0,0,1,1,
	1,1,1,1,1,1,1,4,1,0,1,
	1,1,0,0,0,1,1,0,0,0,1,
	1,1,0,1,0,0,0,0,0,1,1,
	1,1,0,1,0,1,1,1,0,1,1,
	1,1,0,1,0,1,5,1,0,1,1,
	1,1,0,1,0,1,0,0,0,0,1,
	1,2,0,1,0,1,1,0,1,0,1,
	1,1,1,1,1,1,1,1,1,1,1
};

MazeGrid::MazeGrid(SceneGraph* scene) {
	startIndex = -1;
	finishIndex = -1;
	doorIndex = -1;

	// Create the root object and add it to the scene
	rootObject = new GameObject();
	rootObject->SetLocalPosition(glm::vec3(-GRIDSIZE, 0.0f, -GRIDSIZE));
	scene->Add(rootObject);

	// Generate the maze grid based on the grid array
	for (int i = 0; i < GRIDSIZE*GRIDSIZE; i++) {
		mazeGrid[i] = new MazeGridLocation((MazeObjectType)grid[i]);

		// Add the game object of this grid location to the scene graph (as children of root object) if it exists,
		// and set their positions correctly
		if (mazeGrid[i]->GetGameObject()) {
			rootObject->AddChild(mazeGrid[i]->GetGameObject());
			mazeGrid[i]->GetGameObject()->SetLocalPosition(glm::vec3((i % GRIDSIZE) * 2.0f, (MazeObjectType)grid[i] == MazeObjectType::MAZE_WALL ? 0.0f : -2.0f, (i / GRIDSIZE) * 2.0f));
		}

		// Set the start or ending index of the grid
		if ((MazeObjectType)grid[i] == MazeObjectType::MAZE_START)
			startIndex = i;
		if ((MazeObjectType)grid[i] == MazeObjectType::MAZE_END)
			finishIndex = i;
		if ((MazeObjectType)grid[i] == MazeObjectType::MAZE_OBJECT1)
			doorIndex = i;


	}
}

MazeGrid::~MazeGrid() {
	// No need to delete the root object as the scene node will handle it
	// Delete the maze grid location objects
	for (int i = 0; i < GRIDSIZE*GRIDSIZE; i++)
		if (mazeGrid[i]) {
			delete mazeGrid[i];
			mazeGrid[i] = nullptr;
		}
}

MazeGridLocation* MazeGrid::GridByIndex(int _index) {
	return mazeGrid[_index];
}

void MazeGrid::UnlockDoor() {
	mazeGrid[doorIndex]->objectType = MazeObjectType::MAZE_FLOOR;
	GameObject* doorObjectChild = ((DoorObject*)mazeGrid[doorIndex]->GetGameObject())->_doorObjectChild;
	mazeGrid[doorIndex]->GetGameObject()->RemoveChild(doorObjectChild);
}
