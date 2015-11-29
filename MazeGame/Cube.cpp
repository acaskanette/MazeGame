#include "Cube.h"

Cube::Cube(AbstractRenderer* renderer) {
	_model = new Mesh();
	std::vector<Vertex> meshVertices;

	// FRONT FACE
	meshVertices.emplace_back(glm::vec3(-1.0F, -1.0F, 1.0F), glm::vec4(1.0F, 0.0F, 0.0F, 1.0F), glm::vec2(0.0F, 0.0F));
	meshVertices.emplace_back(glm::vec3(1.0F, -1.0F, 1.0F), glm::vec4(1.0F, 0.0F, 0.0F, 1.0F), glm::vec2(1.0F, 0.0F));
	meshVertices.emplace_back(glm::vec3(1.0F, 1.0F, 1.0F), glm::vec4(1.0F, 0.0F, 0.0F, 1.0F), glm::vec2(1.0F, 1.0F));
	meshVertices.emplace_back(glm::vec3(-1.0F, 1.0F, 1.0F), glm::vec4(1.0F, 0.0F, 0.0F, 1.0F), glm::vec2(0.0F, 1.0F));

	// BACK FACE
	meshVertices.emplace_back(glm::vec3(-1.0F, -1.0F, -1.0F), glm::vec4(0.0F, 1.0F, 0.0F, 1.0F), glm::vec2(0.0F, 0.0F));
	meshVertices.emplace_back(glm::vec3(-1.0F, 1.0F, -1.0F), glm::vec4(0.0F, 1.0F, 0.0F, 1.0F), glm::vec2(0.0F, 1.0F));
	meshVertices.emplace_back(glm::vec3(1.0F, 1.0F, -1.0F), glm::vec4(0.0F, 1.0F, 0.0F, 1.0F), glm::vec2(1.0F, 1.0F));
	meshVertices.emplace_back(glm::vec3(1.0F, -1.0F, -1.0F), glm::vec4(0.0F, 1.0F, 0.0F, 1.0F), glm::vec2(1.0F, 0.0F));

	// TOP FACE
	meshVertices.emplace_back(glm::vec3(-1.0F, 1.0F, -1.0F), glm::vec4(0.0F, 0.0F, 1.0F, 1.0F), glm::vec2(0.0F, 0.0F));
	meshVertices.emplace_back(glm::vec3(-1.0F, 1.0F, 1.0F), glm::vec4(0.0F, 0.0F, 1.0F, 1.0F), glm::vec2(0.0F, 1.0F));
	meshVertices.emplace_back(glm::vec3(1.0F, 1.0F, 1.0F), glm::vec4(0.0F, 0.0F, 1.0F, 1.0F), glm::vec2(1.0F, 1.0F));
	meshVertices.emplace_back(glm::vec3(1.0F, 1.0F, -1.0F), glm::vec4(0.0F, 0.0F, 1.0F, 1.0F), glm::vec2(1.0F, 0.0F));

	// BOTTOM FACE
	meshVertices.emplace_back(glm::vec3(-1.0F, -1.0F, -1.0F), glm::vec4(0.0F, 1.0F, 1.0F, 1.0F), glm::vec2(0.0F, 0.0F));
	meshVertices.emplace_back(glm::vec3(1.0F, -1.0F, -1.0F), glm::vec4(0.0F, 1.0F, 1.0F, 1.0F), glm::vec2(1.0F, 0.0F));
	meshVertices.emplace_back(glm::vec3(1.0F, -1.0F, 1.0F), glm::vec4(0.0F, 1.0F, 1.0F, 1.0F), glm::vec2(1.0F, 1.0F));
	meshVertices.emplace_back(glm::vec3(-1.0F, -1.0F, 1.0F), glm::vec4(0.0F, 1.0F, 1.0F, 1.0F), glm::vec2(0.0F, 1.0F));

	// RIGHT FACE
	meshVertices.emplace_back(glm::vec3(1.0F, -1.0F, -1.0F), glm::vec4(1.0F, 1.0F, 0.0F, 1.0F), glm::vec2(0.0F, 0.0F));
	meshVertices.emplace_back(glm::vec3(1.0F, 1.0F, -1.0F), glm::vec4(1.0F, 1.0F, 0.0F, 1.0F), glm::vec2(0.0F, 1.0F));
	meshVertices.emplace_back(glm::vec3(1.0F, 1.0F, 1.0F), glm::vec4(1.0F, 1.0F, 0.0F, 1.0F), glm::vec2(1.0F, 1.0F));
	meshVertices.emplace_back(glm::vec3(1.0F, -1.0F, 1.0F), glm::vec4(1.0F, 1.0F, 0.0F, 1.0F), glm::vec2(1.0F, 0.0F));

	// LEFT FACE
	meshVertices.emplace_back(glm::vec3(-1.0F, -1.0F, -1.0F), glm::vec4(1.0F, 0.0F, 1.0F, 1.0F), glm::vec2(0.0F, 0.0F));
	meshVertices.emplace_back(glm::vec3(-1.0F, -1.0F, 1.0F), glm::vec4(1.0F, 0.0F, 1.0F, 1.0F), glm::vec2(1.0F, 0.0F));
	meshVertices.emplace_back(glm::vec3(-1.0F, 1.0F, 1.0F), glm::vec4(1.0F, 0.0F, 1.0F, 1.0F), glm::vec2(1.0F, 1.0F));
	meshVertices.emplace_back(glm::vec3(-1.0F, 1.0F, -1.0F), glm::vec4(1.0F, 0.0F, 1.0F, 1.0F), glm::vec2(0.0F, 1.0F));

	renderer->InitializeMesh(*_model, meshVertices, "textures/pikachu.png");
}

void Cube::UpdateMe() {

}

void Cube::RenderMe(AbstractRenderer* renderer) {
	renderer->RenderEntity(this);
}