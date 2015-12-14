#pragma once
#include "Mesh.h"

class Model {
public:
	std::vector<Mesh> meshes;

	Model(std::vector<Mesh> meshes);
};