#include "OpenGLRenderer.h"

#include "Loader.h"
#include "LogManager.h"
#include "GameObject.h"
#include "Model.h"
#include "GLSLProgram.h"

#include <sstream>
#include <GLM/gtc/matrix_transform.hpp>

OpenGLRenderer::OpenGLRenderer() {
	GLenum error = glewInit();
	if (glewInit() != GLEW_OK)
		LogManager::GetInstance()->LogFatal("GLEW could not be initialized: " + std::string((const char*)glewGetErrorString(error)));
}

OpenGLRenderer::~OpenGLRenderer() {
	if (m_shaderProgram)
		delete m_shaderProgram;
}

void OpenGLRenderer::InitShaders(const std::string& vertFile, const std::string& fragFile) {
	m_shaderProgram = new GLSLProgram();
	m_shaderProgram->CompileShaders(vertFile, fragFile);
	m_shaderProgram->AddAttribute("vPosition");
	m_shaderProgram->AddAttribute("vColor");
	m_shaderProgram->AddAttribute("vUV");
	m_shaderProgram->AddAttribute("vNormal");
	m_shaderProgram->LinkShaders();
	m_shaderProgram->Use();
}

GLSLProgram* OpenGLRenderer::GetShader() {
	return m_shaderProgram;
}

void OpenGLRenderer::RenderMesh(Mesh* mesh) {
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;

	for (GLuint i = 0; i < mesh->textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding
																			// Retrieve texture number (the N in diffuse_textureN)
		std::stringstream ss;
		std::string number;
		std::string name = mesh->textures[i].type;
		if (name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		number = ss.str();

		glUniform1f(m_shaderProgram->GetUniformLocation((/*"material." + */name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, mesh->textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	glUniform1f(m_shaderProgram->GetUniformLocation("shininess"), 16.0f);

	// Draw mesh
	glBindVertexArray(mesh->vao);
	glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}