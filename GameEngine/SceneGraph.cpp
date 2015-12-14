#include "SceneGraph.h"

SceneGraph::SceneGraph() : m_rootNode(new GameObject()) {}

SceneGraph::~SceneGraph() {
	if (m_rootNode)
		delete m_rootNode;
}

void SceneGraph::Update(GameTime& gameTime) {
	m_rootNode->Update(gameTime);
}

void SceneGraph::Render(AbstractRenderer* renderer) {
	m_rootNode->Render(renderer);
}

void SceneGraph::Add(GameObject* object) {
	m_rootNode->AddChild(object);
}

void SceneGraph::Remove(GameObject* object) {
	m_rootNode->RemoveChild(object);
}