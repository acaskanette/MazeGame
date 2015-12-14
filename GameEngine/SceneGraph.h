#pragma once
#include "GameObject.h"
#include "Camera.h"

class SceneGraph {
public:
	void Update(GameTime& gameTime);
	void Render(AbstractRenderer* renderer);

	void Add(GameObject* object);
	void Remove(GameObject* object);

	SceneGraph();
	~SceneGraph();
private:
	GameObject* m_rootNode;
};