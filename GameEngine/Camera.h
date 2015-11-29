#pragma once
#include "AbstractRenderer.h"
#include <GL/glew.h>
#include <GLM/glm.hpp>

// Handles everything to do with the Camera, including its position, where it's looking, its view frustum, and manual culling
class Camera {
public:
	bool IsInView(const glm::vec3& position, float radius);
	void ResizeWindow(GLfloat newWidth, GLfloat newHeight);

	void UpdateFrustum(AbstractRenderer* renderer);

	void SetPosition(const glm::vec3& position);
	void SetUp(const glm::vec3& up);
	void SetLookAt(const glm::vec3& lookAt);

	const glm::vec3& GetPosition();
	const glm::vec3& GetUp();
	const glm::vec3& GetForward();
	const glm::vec3& GetSceneCentre();
	const glm::mat4& GetModelView();
	const glm::mat4& GetProjection();
	const GLfloat& GetWindowWidth();
	const GLfloat& GetWindowHeight();

	Camera(GLfloat width, GLfloat height);
private:
	glm::vec3 m_position;
	glm::vec3 m_sceneCentre;
	glm::vec3 m_up;
	glm::vec3 m_forward;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	GLfloat m_windowWidth;
	GLfloat m_windowHeight;
	bool m_needsUpdate;
};