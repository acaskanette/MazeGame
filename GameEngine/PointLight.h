#pragma once
#include "GameObject.h"

class PointLight : public GameObject {
public:
	virtual void RenderMe(AbstractRenderer* renderer) override;

	const glm::vec3& GetAmbient();
	const glm::vec3& GetDiffuse();
	const glm::vec3& GetSpecular();

	void SetAmbient(const glm::vec3& ambient);
	void SetDiffuse(const glm::vec3& diffuse);
	void SetSpecular(const glm::vec3& specular);

	PointLight();
private:
	static int idIndex;

	int id;
	glm::vec3 _ambient;
	glm::vec3 _diffuse;
	glm::vec3 _specular;
};