#pragma once
#include "AbstractRenderer.h"
#include "GameObject.h"

// Handles everything to do with the Camera, including its position, where it's looking, its view frustum, and manual culling
class Camera : public GameObject {
public:
	bool IsInView(const glm::vec3& position, float radius);
	void ResizeWindow(GLfloat newWidth, GLfloat newHeight);

	virtual void UpdateMe(GameTime& gameTime) override;

	virtual void SetLocalPosition(const glm::vec3& position) override;
	void SetUp(const glm::vec3& up);
	void SetForward(const glm::vec3& lookAt);
	void ForceUpdate();

	const glm::vec3& GetUp();
	const glm::vec3& GetForward();
	const glm::vec3 GetRight();
	const glm::mat4& GetModelView();
	const glm::mat4& GetProjection();
	const GLfloat& GetWindowWidth();
	const GLfloat& GetWindowHeight();

	Camera(AbstractRenderer* renderer, GLfloat width, GLfloat height);
private:
	AbstractRenderer* m_renderer;
	glm::vec3 m_up;
	glm::vec3 m_forward;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	GLfloat m_windowWidth;
	GLfloat m_windowHeight;
	bool m_needsUpdate;
};