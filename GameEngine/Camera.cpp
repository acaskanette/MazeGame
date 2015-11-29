#include "Camera.h"
#include <GLM/gtc/matrix_transform.hpp>

Camera::Camera(GLfloat width, GLfloat height) {
	m_position = glm::vec3(0.0F, 0.0F, 15.0F);
	m_sceneCentre = glm::vec3(0.0F, 0.0F, 0.0F);
	m_up = glm::vec3(0.0F, 1.0F, 0.0F);
	m_forward = m_sceneCentre - m_position;
	m_windowWidth = width;
	m_windowHeight = height;
	m_needsUpdate = true;
}

void Camera::ResizeWindow(GLfloat newWidth, GLfloat newHeight) {
	m_windowWidth = newWidth;
	m_windowHeight = newHeight;
	m_needsUpdate = true;
}

void Camera::UpdateFrustum(AbstractRenderer* renderer) {
	if (m_needsUpdate) {
		m_forward = m_sceneCentre - m_position;
		m_viewMatrix = glm::lookAt(m_position, m_sceneCentre, m_up);
		m_projectionMatrix = glm::perspective(45.0f, m_windowWidth / m_windowHeight, 0.1f, 200.0f); // angle, aspect ratio, near, far
		
		renderer->UpdateFrustum(m_viewMatrix, m_projectionMatrix);

		m_needsUpdate = false;
	}
}

void Camera::SetPosition(const glm::vec3& position) {
	m_position = position;
	m_needsUpdate = true;
}

void Camera::SetUp(const glm::vec3& up) {
	m_up = up;
	m_needsUpdate = true;
}

void Camera::SetLookAt(const glm::vec3& lookAt) {
	m_sceneCentre = lookAt;
	m_needsUpdate = true;
}

const glm::vec3& Camera::GetPosition() {
	return m_position;
}

const glm::vec3& Camera::GetUp() {
	return m_up;
}

const glm::vec3& Camera::GetForward() {
	return m_forward;
}

const glm::vec3& Camera::GetSceneCentre() {
	return m_sceneCentre;
}

const glm::mat4& Camera::GetModelView() {
	return m_viewMatrix;
}

const glm::mat4& Camera::GetProjection() {
	return m_projectionMatrix;
}

const GLfloat& Camera::GetWindowWidth() {
	return m_windowWidth;
}

const GLfloat& Camera::GetWindowHeight() {
	return m_windowHeight;
}

bool Camera::IsInView(const glm::vec3& position, float radius) {
	enum plane_terms { A = 0, B, C, D };
	
	const glm::mat4 mvp = m_projectionMatrix * m_viewMatrix;
	const GLfloat &x = position.x, &y = position.y, &z = position.z;

	GLfloat leftPlane[4];
	leftPlane[A] = mvp[0][3] + mvp[0][0];
	leftPlane[B] = mvp[1][3] + mvp[1][0];
	leftPlane[C] = mvp[2][3] + mvp[2][0];
	leftPlane[D] = mvp[3][3] + mvp[3][0];

	// Normalise the plane
	GLfloat length = sqrtf(leftPlane[A] * leftPlane[A] + leftPlane[B] * leftPlane[B] + leftPlane[C] * leftPlane[C]);
	leftPlane[A] /= length;
	leftPlane[B] /= length;
	leftPlane[C] /= length;
	leftPlane[D] /= length;

	// Check the point's location with respect to the left plane of our viewing frustrum
	GLfloat distance = leftPlane[A] * x + leftPlane[B] * y + leftPlane[C] * z + leftPlane[D];
	if (distance <= -radius)
		return false; // Bounding sphere is completely outside the left plane

	// Check the point's location with respect to the right plane of our viewing frustum
	GLfloat rightPlane[4];
	rightPlane[A] = mvp[0][3] - mvp[0][0];
	rightPlane[B] = mvp[1][3] - mvp[1][0];
	rightPlane[C] = mvp[2][3] - mvp[2][0];
	rightPlane[D] = mvp[3][3] - mvp[3][0];

	// Normalise the plane
	length = sqrtf(rightPlane[A] * rightPlane[A] + rightPlane[B] * rightPlane[B] + rightPlane[C] * rightPlane[C]);
	rightPlane[A] /= length;
	rightPlane[B] /= length;
	rightPlane[C] /= length;
	rightPlane[D] /= length;

	distance = rightPlane[A] * x + rightPlane[B] * y + rightPlane[C] * z + rightPlane[D];
	if (distance <= -radius)
		return false; // Bounding sphere is completely outside the right plane

	// Check the point's location with respect to the bottom plane of our viewing frustum
	GLfloat bottomPlane[4];
	bottomPlane[A] = mvp[0][3] + mvp[0][1];
	bottomPlane[B] = mvp[1][3] + mvp[1][1];
	bottomPlane[C] = mvp[2][3] + mvp[2][1];
	bottomPlane[D] = mvp[3][3] + mvp[3][1];

	// Normalise the plane
	length = sqrtf(bottomPlane[A] * bottomPlane[A] + bottomPlane[B] * bottomPlane[B] + bottomPlane[C] * bottomPlane[C]);
	bottomPlane[A] /= length;
	bottomPlane[B] /= length;
	bottomPlane[C] /= length;
	bottomPlane[D] /= length;

	distance = bottomPlane[A] * x + bottomPlane[B] * y + bottomPlane[C] * z + bottomPlane[D];
	if (distance <= -radius)
		return false; // Bounding sphere is completely outside the bottom plane

	// Check the point's location with respect to the top plane of our viewing frustrum
	GLfloat topPlane[4];
	topPlane[A] = mvp[0][3] - mvp[0][1];
	topPlane[B] = mvp[1][3] - mvp[1][1];
	topPlane[C] = mvp[2][3] - mvp[2][1];
	topPlane[D] = mvp[3][3] - mvp[3][1];

	// Normalise the plane
	length = sqrtf(topPlane[A] * topPlane[A] + topPlane[B] * topPlane[B] + topPlane[C] * topPlane[C]);
	topPlane[A] /= length;
	topPlane[B] /= length;
	topPlane[C] /= length;
	topPlane[D] /= length;

	distance = topPlane[A] * x + topPlane[B] * y + topPlane[C] * z + topPlane[D];
	if (distance <= -radius)
		return false; // Bounding sphere is completely outside the top plane

	// Check the point's location with respect to the near plane of our viewing frustum
	GLfloat nearPlane[4];
	nearPlane[A] = mvp[0][3] + mvp[0][2];
	nearPlane[B] = mvp[1][3] + mvp[1][2];
	nearPlane[C] = mvp[2][3] + mvp[2][2];
	nearPlane[D] = mvp[3][3] + mvp[3][2];

	// Normalise the plane
	length = sqrtf(nearPlane[A] * nearPlane[A] + nearPlane[B] * nearPlane[B] + nearPlane[C] * nearPlane[C]);
	nearPlane[A] /= length;
	nearPlane[B] /= length;
	nearPlane[C] /= length;
	nearPlane[D] /= length;

	distance = nearPlane[A] * x + nearPlane[B] * y + nearPlane[C] * z + nearPlane[D];
	if (distance <= -radius)
		return false; // Bounding sphere is completely outside the near plane

	// Check the point's location with respect to the far plane of our viewing frustum
	GLfloat farPlane[4];
	farPlane[A] = mvp[0][3] - mvp[0][2];
	farPlane[B] = mvp[1][3] - mvp[1][2];
	farPlane[C] = mvp[2][3] - mvp[2][2];
	farPlane[D] = mvp[3][3] - mvp[3][2];

	// Normalise the plane
	length = sqrtf(farPlane[A] * farPlane[A] + farPlane[B] * farPlane[B] + farPlane[C] * farPlane[C]);
	farPlane[A] /= length;
	farPlane[B] /= length;
	farPlane[C] /= length;
	farPlane[D] /= length;

	distance = farPlane[A] * x + farPlane[B] * y + farPlane[C] * z + farPlane[D];
	if (distance <= -radius)
		return false; // Bounding sphere is completely outside the far plane

	// If the function did not return by now, it's inside the frustum
	return true;
}