#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include "AbstractRenderer.h"

class OpenGLRenderer : public AbstractRenderer {
public:
	virtual void InitShaders(const std::string& vertFile, const std::string& fragFile) override;
	virtual void RenderMesh(Mesh* mesh) override;
	virtual GLSLProgram* GetShader() override;

	OpenGLRenderer();
	~OpenGLRenderer();
private:
	GLSLProgram* m_shaderProgram;
};