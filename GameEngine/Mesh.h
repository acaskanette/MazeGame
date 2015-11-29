#pragma once
#include <vector>
#include "Vertex.h"
#include "GLTexture.h"

struct Mesh {
	std::vector<Vertex> vertices;
	GLuint vao, vbo;
	GLTexture texture;

	Mesh() : vao(0), vbo(0), texture() {}
	~Mesh() {}
};