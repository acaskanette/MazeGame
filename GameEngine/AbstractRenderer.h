#pragma once
#include <vector>
#include <GLM/glm.hpp>
#include "Primitive.h"

struct Mesh;
struct Vertex;
class GameObject;

class AbstractRenderer {
public:
	virtual void InitializeMesh(Mesh&, const std::vector<Vertex>&, const std::string&) = 0;

	virtual void RenderPrimitive(const PrimitiveType&, const std::vector<Vertex>&) = 0;
	virtual void RenderMesh(const Mesh&) = 0;
	virtual void RenderEntity(GameObject*) = 0;

	virtual void UpdateFrustum(const glm::mat4& view, const glm::mat4& projection) = 0;

	AbstractRenderer() {}
};