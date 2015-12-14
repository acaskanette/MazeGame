#pragma once

#include <GameObject.h>
#include <ResourceManager.h>
#include <Model.h>
#include "Cube.h"

class DoorObjectChild : public GameObject {
public:
	virtual void RenderMe(AbstractRenderer* renderer) override {
		for (int i = 0; i < _model->meshes.size(); i++)
			renderer->RenderMesh(&_model->meshes[i]);
	}

	DoorObjectChild(std::string modelName, float scale) {
		_model = ResourceManager::GetInstance()->LoadModel(modelName);
		SetScale(glm::vec3(scale, scale, scale));
	}
private:
	Model* _model;
};

class DoorObject : public GameObject {
public:
	DoorObject(std::string modelName, float scale) {
		AddChild(_doorObjectChild = new DoorObjectChild(modelName, scale));
		_doorObjectChild->SetLocalPosition(glm::vec3(-0.3f, 2.0f, -6.5f));
		_floorCube = new Cube("models/crate/crate.obj");
		AddChild(_floorCube);
	}
	
	GameObject* _doorObjectChild;

private:

	GameObject* _floorCube;

};