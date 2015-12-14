#pragma once
#include <vector>
#include "Vertex.h"
#include "Texture.h"

class Mesh {
public:
	GLuint vao, vbo, ebo;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
};