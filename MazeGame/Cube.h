#pragma once
#include <GameObject.h>
#include <ResourceManager.h>
#include <Model.h>

class Cube : public GameObject {
public:
	virtual void RenderMe(AbstractRenderer* renderer) override {
		for (int i = 0; i < _model->meshes.size(); i++)
			renderer->RenderMesh(&_model->meshes[i]);
	}

	Cube(std::string modelName) {
		_model = ResourceManager::GetInstance()->LoadModel(modelName);
		SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	}
private:
	Model* _model;
};