#include "OpenGLRenderer.h"

#include "Loader.h"
#include "LogManager.h"
#include "GameObject.h"
#include "Mesh.h"

#include <GLM/gtc/matrix_transform.hpp>

OpenGLRenderer::OpenGLRenderer() {
	GLenum error = glewInit();
	if (glewInit() != GLEW_OK)
		LogManager::getInstance().logFatal("GLEW could not be initialized: " + std::string((const char*)glewGetErrorString(error)));

	// The default texture will be a 1x1 white square
	glGenTextures(1, &defaultTexture.id);
	glBindTexture(GL_TEXTURE_2D, defaultTexture.id);
	defaultTexture.width = 1;
	defaultTexture.height = 1;

	GLfloat texture_image[] = {
		1.0f, 1.0f, 1.0f, 1.0f
	};

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, defaultTexture.width, defaultTexture.height, 0, GL_RGBA, GL_FLOAT, texture_image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLRenderer::InitShaders(const std::string& vertFile, const std::string& fragFile) {
	m_shaderProgram.CompileShaders(vertFile, fragFile);
	m_shaderProgram.AddAttribute("vPosition");
	m_shaderProgram.AddAttribute("vColor");
	m_shaderProgram.AddAttribute("vUV");
	m_shaderProgram.AddAttribute("vNormal");
	m_shaderProgram.LinkShaders();
	m_shaderProgram.Use();
}

void OpenGLRenderer::InitializeMesh(Mesh& _mesh, const std::vector<Vertex>& vertices, const std::string& textureFileName) {
	_mesh.vertices = vertices;
	_mesh.texture = Loader::LoadPNG(textureFileName);

	// Generate the mesh's vertex array object and vertex buffer object
	glGenVertexArrays(1, &_mesh.vao);
	glBindVertexArray(_mesh.vao);
	glGenBuffers(1, &_mesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _mesh.vbo);

	// Set the position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	// Set the color attribute pointer
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	// Set the UV attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glEnableVertexAttribArray(2);
	// Set the normal attribute pointer
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	// Unbind the buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLSLProgram& OpenGLRenderer::GetShader() {
	return m_shaderProgram;
}

void OpenGLRenderer::RenderPrimitive(const PrimitiveType& primitiveType, const std::vector<Vertex>& vertices) {
	std::vector<Vertex> verts = vertices;

	// If verts were not defined, use the default verts for the given primitive type
	if (verts.empty()) {
		switch (primitiveType) {
		case POINT:
			verts.emplace_back(glm::vec3(0.0F, 0.0F, 0.0F), glm::vec4(1.0F, 0.0F, 1.0F, 1.0F), glm::vec2(0.0F, 0.0F));
			break;
		case LINE:
			verts.emplace_back(glm::vec3(-1.0F, 0.0F, 0.0F), glm::vec4(0.0F, 0.0F, 1.0F, 1.0F), glm::vec2(0.0F, 0.5F));
			verts.emplace_back(glm::vec3(1.0F, 0.0F, 0.0F), glm::vec4(0.0F, 0.0F, 1.0F, 1.0F), glm::vec2(1.0F, 0.5F));
			break;
		case TRIANGLE:
			verts.emplace_back(glm::vec3(-1.0F, -1.0F, 0.0F), glm::vec4(0.0F, 1.0F, 0.0F, 1.0F), glm::vec2(0.0F, 0.0F));
			verts.emplace_back(glm::vec3(0.0F, 1.0F, 0.0F), glm::vec4(1.0F, 0.0F, 0.0F, 1.0F), glm::vec2(0.5F, 1.0F));
			verts.emplace_back(glm::vec3(1.0F, -1.0F, 0.0F), glm::vec4(0.0F, 0.0F, 1.0F, 1.0F), glm::vec2(1.0F, 0.0F));
			break;
		case QUAD:
			verts.emplace_back(glm::vec3(-1.0F, -1.0F, 0.0F), glm::vec4(1.0F, 0.0F, 1.0F, 1.0F), glm::vec2(0.0F, 0.0F));
			verts.emplace_back(glm::vec3(1.0F, -1.0F, 0.0F), glm::vec4(1.0F, 0.0F, 0.0F, 1.0F), glm::vec2(1.0F, 0.0F));
			verts.emplace_back(glm::vec3(1.0F, 1.0F, 0.0F), glm::vec4(0.0F, 1.0F, 0.0F, 1.0F), glm::vec2(1.0F, 1.0F));
			verts.emplace_back(glm::vec3(-1.0F, 1.0F, 0.0F), glm::vec4(0.0F, 0.0F, 1.0F, 1.0F), glm::vec2(0.0F, 1.0F));
			break;
		default:
			return;
		}
	}

	// Generate the temp VAO and VBO and bind them
	glGenVertexArrays(1, &primitiveVao);
	glBindVertexArray(primitiveVao);
	glGenBuffers(1, &primitiveVbo);
	glBindBuffer(GL_ARRAY_BUFFER, primitiveVbo);

	// Set the position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	// Set the color attribute pointer
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	// Set the UV attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glEnableVertexAttribArray(2);
	// Set the normal attribute pointer
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	// Orphan the buffer
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	// Upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, verts.size() * sizeof(Vertex), verts.data());

	// Bind the default texture
	glBindTexture(GL_TEXTURE_2D, defaultTexture.id);
	switch (primitiveType) {
	case POINT:
		glDrawArrays(GL_POINTS, 0, verts.size());
		break;
	case LINE:
		glDrawArrays(GL_LINES, 0, verts.size());
		break;
	case TRIANGLE:
		glDrawArrays(GL_TRIANGLES, 0, verts.size());
		break;
	case QUAD:
		glDrawArrays(GL_QUADS, 0, verts.size());
		break;
	}

	// Unbind the default texture
	glBindTexture(GL_TEXTURE_2D, 0);
	// Unbind the temp VAO, VBO, and clear them from memory
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &primitiveVao);
	glDeleteBuffers(1, &primitiveVbo);
}

void OpenGLRenderer::RenderMesh(const Mesh& mesh) {
	size_t size = mesh.vertices.size();

	// Bind the mesh's buffers
	glBindVertexArray(mesh.vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

	// Orphan the buffer
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	// Upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(Vertex), mesh.vertices.data());

	glBindTexture(GL_TEXTURE_2D, mesh.texture.id);
	glDrawArrays(GL_QUADS, 0, size);

	// Unbind the buffers
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void OpenGLRenderer::RenderEntity(GameObject* gameObject) {
	glUniformMatrix4fv(m_shaderProgram.GetUniformLocation("TransformMatrix"), 1, GL_FALSE, &gameObject->GetTransform()[0][0]);
	
	RenderMesh(gameObject->GetModel());
}

void OpenGLRenderer::UpdateFrustum(const glm::mat4& view, const glm::mat4& projection) {
	glUniformMatrix4fv(m_shaderProgram.GetUniformLocation("ProjectionMatrix"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(m_shaderProgram.GetUniformLocation("CameraViewMatrix"), 1, GL_FALSE, &view[0][0]);
}