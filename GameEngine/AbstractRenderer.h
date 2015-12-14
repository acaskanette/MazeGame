#pragma once
#include <vector>
#include <GLM/glm.hpp>
#include "GLSLProgram.h"

class Mesh;

class AbstractRenderer {
public:
	virtual void InitShaders(const std::string&, const std::string&) = 0;
	virtual void RenderMesh(Mesh*) = 0;
	virtual GLSLProgram* GetShader() = 0;
};