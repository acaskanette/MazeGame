#pragma once
#include "GameObject.h"
#include "Camera.h"

class SceneGraph {
public:
	void Update();
	void Render(AbstractRenderer* renderer);

	void Add(GameObject* object);
	void Remove(GameObject* object);

	void SetMainCamera(Camera* cam);
	Camera& GetMainCamera();

	SceneGraph();
	~SceneGraph();
private:
	GameObject* m_rootNode;
	Camera* m_mainCamera;
};