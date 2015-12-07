#include "FloorStart.h"

FloorStart::FloorStart(AbstractRenderer* renderer)
{
	_model = new Mesh();
	std::vector<Vertex> meshVertices;

	// BOTTOM FACE
	meshVertices.emplace_back(glm::vec3(-1.0F, -1.0F, -1.0F), glm::vec4(1.0F, 1.0F, 1.0F, 1.0F), glm::vec2(0.0F, 0.0F));
	meshVertices.emplace_back(glm::vec3(1.0F, -1.0F, -1.0F), glm::vec4(1.0F, 1.0F, 1.0F, 1.0F), glm::vec2(0.0F, 1.0F));
	meshVertices.emplace_back(glm::vec3(1.0F, -1.0F, 1.0F), glm::vec4(1.0F, 1.0F, 1.0F, 1.0F), glm::vec2(1.0F, 1.0F));
	meshVertices.emplace_back(glm::vec3(-1.0F, -1.0F, 1.0F), glm::vec4(1.0F, 1.0F, 1.0F, 1.0F), glm::vec2(1.0F, 0.0F));

	renderer->InitializeMesh(*_model, meshVertices, "textures/floorstart.png");

}

void FloorStart::UpdateMe() {

}

void FloorStart::RenderMe(AbstractRenderer* renderer) {
	renderer->RenderEntity(this);
}