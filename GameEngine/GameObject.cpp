#include "GameObject.h"

#include <GLM/gtc/matrix_transform.hpp>

GameObject::GameObject() : _parent(nullptr), _firstChild(nullptr), _lastChild(nullptr), _prevSibling(nullptr), _nextSibling(nullptr), _model(nullptr) {
	_position = glm::vec3(0.0F, 0.0F, 0.0F);
	_axis = glm::vec3(0.0F, 1.0F, 0.0F);
	_angle = 0;
	_scale = glm::vec3(1.0F, 1.0F, 1.0F);
}

GameObject::~GameObject() {
	if (_model)
		delete _model;
	if (_nextSibling)
		delete _nextSibling;
	if (_firstChild)
		delete _firstChild;
}

void GameObject::Update() {
	// If not the root node
	if (_parent) {
		UpdateMe(); // Update self

		// Breadth first
		// Then update siblings
		if (_nextSibling)
			_nextSibling->Update();
	}

	// Then update children
	if (_firstChild)
		_firstChild->Update();
}

void GameObject::Render(AbstractRenderer* renderer) {
	// If not the root node
	if (_parent) {
		RenderMe(renderer); // Render self

		// Then render siblings
		if (_nextSibling)
			_nextSibling->Render(renderer);
	}

	// Then render children
	if (_firstChild)
		_firstChild->Render(renderer);
}

void GameObject::AddChild(GameObject* object) {
	// If there isn't a last child there isn't a first child
	if (!_lastChild)
		_firstChild = object;
	else {
		// Set the last child's next sibling as the added object (making it the last child)
		_lastChild->_nextSibling = object;
		// Set the object's previous sibling as the old last child
		object->_prevSibling = _lastChild;
	}

	// Set the object to be the last child and add a pointer to the parent
	_lastChild = object;
	object->_parent = this;
}

void GameObject::RemoveChild(GameObject* object) {
	GameObject* currentNode = nullptr;

	// Loop through the children until the object to be removed is found
	for (currentNode = _firstChild; currentNode != nullptr; currentNode = currentNode->_nextSibling) {
		if (currentNode == object) {
			// If the object has a previous sibling, set its next sibling as the removed objects next sibling
			if (object->_prevSibling)
				object->_prevSibling->_nextSibling = object->_nextSibling;
			else // Otherwise just set the first child as the object's next sibling
				_firstChild = object->_nextSibling;

			// If the object has a next sibling, set its previous sibling as the object's previous sibling
			if (object->_nextSibling)
				object->_nextSibling->_prevSibling = object->_prevSibling;
			else // Otherwise just set the last child as the object's previous sibling
				_lastChild = object->_prevSibling;

			object->_parent = nullptr; // Remove the pointer to the parent
			break;
		}
	}
}

const glm::mat4 GameObject::GetTransform() {
	glm::mat4 transform;
	if (_parent) // Get the parent's transforms
		transform = _parent->GetTransform();
	else         // Root node would have this
		transform = glm::mat4(1.0F);

	// Apply scale, rotation, and translation to the parent transform and return it
	transform = glm::scale(transform, GetScale());
	transform = glm::translate(transform, GetLocalPosition());
	transform = glm::rotate(transform, GetRotationAngle(), GetRotationAxis());

	return transform;
}

const glm::vec3& GameObject::GetLocalPosition() { 
	return _position; 
}

const glm::vec3 GameObject::GetWorldPosition() {
	glm::mat4 transform = GetTransform();
	glm::vec3 worldPosition = glm::vec3(transform[3][0], transform[3][1], transform[3][2]);

	return worldPosition;
}

const glm::vec3& GameObject::GetRotationAxis() { 
	return _axis; 
}

const GLfloat& GameObject::GetRotationAngle() { 
	return _angle; 
}

const glm::vec3& GameObject::GetScale() { 
	return _scale; 
}

const Mesh& GameObject::GetModel() { 
	return *_model; 
}

GameObject* GameObject::GetParent() {
	return _parent;
}

void GameObject::SetLocalPosition(const glm::vec3& position) { 
	_position = position; 
}

void GameObject::SetRotationAxis(const glm::vec3& axis) { 
	_axis = axis; 
}

void GameObject::SetRotationAngle(const GLfloat& angle) { 
	_angle = angle; 
}

void GameObject::SetScale(const glm::vec3& scale) { 
	_scale = scale; 
}