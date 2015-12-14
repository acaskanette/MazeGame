#include "PointLight.h"

int PointLight::idIndex = 0;

PointLight::PointLight() : _ambient(glm::vec3(0.05f)), _diffuse(glm::vec3(1.0f)), _specular(glm::vec3(1.0f)) {
	id = idIndex++;
}

void PointLight::RenderMe(AbstractRenderer* renderer) {
	std::string pointLightId = "pointLights[" + std::to_string(id) + "]";
	glUniform3f(renderer->GetShader()->GetUniformLocation(pointLightId + ".position"), GetWorldPosition().x, GetWorldPosition().y, GetWorldPosition().z);
	glUniform3f(renderer->GetShader()->GetUniformLocation(pointLightId + ".ambient"), _ambient.r, _ambient.g, _ambient.b);
	glUniform3f(renderer->GetShader()->GetUniformLocation(pointLightId + ".diffuse"), _diffuse.r, _diffuse.g, _diffuse.b);
	glUniform3f(renderer->GetShader()->GetUniformLocation(pointLightId + ".specular"), _specular.r, _specular.g, _specular.b);
	glUniform1f(renderer->GetShader()->GetUniformLocation(pointLightId + ".linear"), 0.009f);
	glUniform1f(renderer->GetShader()->GetUniformLocation(pointLightId + ".quadratic"), 0.0032f);
}

const glm::vec3& PointLight::GetAmbient() {
	return _ambient;
}

const glm::vec3& PointLight::GetDiffuse() {
	return _diffuse;
}

const glm::vec3& PointLight::GetSpecular() {
	return _specular;
}

void PointLight::SetAmbient(const glm::vec3& ambient) {
	_ambient = ambient;
}

void PointLight::SetDiffuse(const glm::vec3& diffuse) {
	_diffuse = diffuse;
}

void PointLight::SetSpecular(const glm::vec3& specular) {
	_specular = specular;
}