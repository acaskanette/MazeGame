#include "GameObject.h"

#include <GLM/gtc/matrix_transform.hpp>

GameObject::GameObject() : m_parent(nullptr), m_firstChild(nullptr), m_lastChild(nullptr), m_prevSibling(nullptr), m_nextSibling(nullptr) {
	m_position = glm::vec3(0.0F, 0.0F, 0.0F);
	m_axis = glm::vec3(0.0F, 1.0F, 0.0F);
	m_angle = 0;
	m_scale = glm::vec3(1.0F, 1.0F, 1.0F);
}

GameObject::~GameObject() {
	if (m_nextSibling)
		delete m_nextSibling;
	if (m_firstChild)
		delete m_firstChild;
}

void GameObject::Update(GameTime& gameTime) {
	// If not the root node
	if (m_parent) {
		UpdateMe(gameTime); // Update self

		// Breadth first
		// Then update siblings
		if (m_nextSibling)
			m_nextSibling->Update(gameTime);
	}

	// Then update children
	if (m_firstChild)
		m_firstChild->Update(gameTime);
}

void GameObject::Render(AbstractRenderer* renderer) {
	// If not the root node
	if (m_parent) {
		glUniformMatrix4fv(renderer->GetShader()->GetUniformLocation("transformMatrix"), 1, GL_FALSE, &GetTransform()[0][0]);
		RenderMe(renderer); // Render self

		// Then render siblings
		if (m_nextSibling)
			m_nextSibling->Render(renderer);
	}

	// Then render children
	if (m_firstChild)
		m_firstChild->Render(renderer);
}

void GameObject::AddChild(GameObject* object) {
	// If there isn't a last child there isn't a first child
	if (!m_lastChild)
		m_firstChild = object;
	else {
		// Set the last child's next sibling as the added object (making it the last child)
		m_lastChild->m_nextSibling = object;
		// Set the object's previous sibling as the old last child
		object->m_prevSibling = m_lastChild;
	}

	// Set the object to be the last child and add a pointer to the parent
	m_lastChild = object;
	object->m_parent = this;
}

void GameObject::RemoveChild(GameObject* object) {
	GameObject* currentNode = nullptr;

	// Loop through the children until the object to be removed is found
	for (currentNode = m_firstChild; currentNode != nullptr; currentNode = currentNode->m_nextSibling) {
		if (currentNode == object) {
			// If the object has a previous sibling, set its next sibling as the removed objects next sibling
			if (object->m_prevSibling)
				object->m_prevSibling->m_nextSibling = object->m_nextSibling;
			else // Otherwise just set the first child as the object's next sibling
				m_firstChild = object->m_nextSibling;

			// If the object has a next sibling, set its previous sibling as the object's previous sibling
			if (object->m_nextSibling)
				object->m_nextSibling->m_prevSibling = object->m_prevSibling;
			else // Otherwise just set the last child as the object's previous sibling
				m_lastChild = object->m_prevSibling;

			object->m_parent = nullptr; // Remove the pointer to the parent
			break;
		}
	}
}

const glm::mat4 GameObject::GetTransform() {
	glm::mat4 transform;
	if (m_parent) // Get the parent's transforms
		transform = m_parent->GetTransform();
	else         // Root node would have this
		transform = glm::mat4(1.0F);

	// Apply scale, rotation, and translation to the parent transform and return it
	transform = glm::translate(transform, GetLocalPosition());
	transform = glm::rotate(transform, GetRotationAngle(), GetRotationAxis());
	transform = glm::scale(transform, GetScale());

	return transform;
}

const glm::vec3& GameObject::GetLocalPosition() { 
	return m_position; 
}

const glm::vec3 GameObject::GetWorldPosition() {
	glm::mat4 transform = GetTransform();
	glm::vec3 worldPosition = glm::vec3(transform[3][0], transform[3][1], transform[3][2]);

	return worldPosition;
}

const glm::vec3& GameObject::GetRotationAxis() { 
	return m_axis; 
}

const GLfloat& GameObject::GetRotationAngle() { 
	return m_angle; 
}

const glm::vec3& GameObject::GetScale() { 
	return m_scale; 
}

GameObject* GameObject::GetParent() {
	return m_parent;
}

void GameObject::SetLocalPosition(const glm::vec3& position) { 
	m_position = position; 
}

void GameObject::SetRotationAxis(const glm::vec3& axis) { 
	m_axis = axis; 
}

void GameObject::SetRotationAngle(const GLfloat& angle) { 
	m_angle = angle; 
}

void GameObject::SetScale(const glm::vec3& scale) { 
	m_scale = scale; 
}