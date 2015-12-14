#pragma once

#include <GameObject.h>
#include <ResourceManager.h>
#include <Model.h>
#include "Cube.h"

class KeyObjectChild : public GameObject {
public:
	virtual void RenderMe(AbstractRenderer* renderer) override {
		for (int i = 0; i < _model->meshes.size(); i++)
			renderer->RenderMesh(&_model->meshes[i]);
	}

	KeyObjectChild(std::string modelName, float scale) {
		_model = ResourceManager::GetInstance()->LoadModel(modelName);
		SetScale(glm::vec3(scale, scale, scale));
	}
private:
	Model* _model;
};

class KeyObject : public GameObject {
public:
	KeyObject(std::string modelName, float scale) {
		AddChild(_gameObject = new KeyObjectChild(modelName, scale));
		_gameObject->SetLocalPosition(glm::vec3(-0.3f, 2.0f, -6.5f));
		_floorCube = new Cube("models/crate/crate.obj");
		AddChild(_floorCube);
	}
private:
	GameObject* _gameObject;
	GameObject* _floorCube;
};