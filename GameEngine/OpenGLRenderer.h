#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include "AbstractRenderer.h"
#include "GLSLProgram.h"
#include "GLTexture.h"

class OpenGLRenderer : public AbstractRenderer {
public:
	void InitShaders(const std::string& vertFile, const std::string& fragFile);
	virtual void InitializeMesh(Mesh& mesh, const std::vector<Vertex>& vertices, const std::string& textureFileName) override;

	virtual void RenderPrimitive(const PrimitiveType& type, const std::vector<Vertex>& vertices = {}) override;
	virtual void RenderMesh(const Mesh& mesh) override;
	virtual void RenderEntity(GameObject* gameObject) override;

	virtual void UpdateFrustum(const glm::mat4& view, const glm::mat4& projection) override;

	GLSLProgram& GetShader();

	OpenGLRenderer();
private:
	GLSLProgram m_shaderProgram;
	GLuint primitiveVao, primitiveVbo;
	GLTexture defaultTexture;
};