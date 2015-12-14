#pragma once
#include "AbstractRenderer.h"
#include "GameTime.h"

class GameObject {
public:
	void Update(GameTime& gameTime);
	void Render(AbstractRenderer* renderer);

	void AddChild(GameObject* object);
	void RemoveChild(GameObject* object);

	const glm::mat4 GetTransform();
	const glm::vec3& GetLocalPosition();
	const glm::vec3 GetWorldPosition();
	const glm::vec3& GetRotationAxis();
	const GLfloat& GetRotationAngle();
	const glm::vec3& GetScale();

	GameObject* GetParent();

	virtual void SetLocalPosition(const glm::vec3& position);
	virtual void SetRotationAxis(const glm::vec3& axis);
	virtual void SetRotationAngle(const GLfloat& angle);
	virtual void SetScale(const glm::vec3& scale);

	GameObject();
	virtual ~GameObject();
protected:
	GameObject* m_parent;
	GameObject* m_firstChild;
	GameObject* m_lastChild;
	GameObject* m_prevSibling;
	GameObject* m_nextSibling;

	glm::vec3 m_position;
	glm::vec3 m_axis;
	GLfloat m_angle;
	glm::vec3 m_scale;

	virtual void UpdateMe(GameTime& gameTime) {}
	virtual void RenderMe(AbstractRenderer* renderer) {}
};