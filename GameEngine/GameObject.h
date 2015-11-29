#pragma once
#include "AbstractRenderer.h"
#include "Mesh.h"

class GameObject {
public:
	void Update();
	void Render(AbstractRenderer* renderer);

	void AddChild(GameObject* object);
	void RemoveChild(GameObject* object);

	const glm::mat4 GetTransform();
	const glm::vec3& GetLocalPosition();
	const glm::vec3 GetWorldPosition();
	const glm::vec3& GetRotationAxis();
	const GLfloat& GetRotationAngle();
	const glm::vec3& GetScale();
	const Mesh& GetModel();

	GameObject* GetParent();

	void SetLocalPosition(const glm::vec3& position);
	void SetRotationAxis(const glm::vec3& axis);
	void SetRotationAngle(const GLfloat& angle);
	void SetScale(const glm::vec3& scale);

	GameObject();
	virtual ~GameObject();
protected:
	GameObject* _parent;
	GameObject* _firstChild;
	GameObject* _lastChild;
	GameObject* _prevSibling;
	GameObject* _nextSibling;

	glm::vec3 _position;
	glm::vec3 _axis;
	GLfloat _angle;
	glm::vec3 _scale;

	Mesh* _model;

	virtual void UpdateMe() {}
	virtual void RenderMe(AbstractRenderer* renderer) {}
};