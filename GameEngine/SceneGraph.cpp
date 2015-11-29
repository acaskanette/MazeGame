#include "SceneGraph.h"

SceneGraph::SceneGraph() : m_rootNode(new GameObject()), m_mainCamera(nullptr) {}

SceneGraph::~SceneGraph() {
	if (m_rootNode)
		delete m_rootNode;
	if (m_mainCamera)
		delete m_mainCamera;
}

void SceneGraph::Update() {
	m_rootNode->Update();
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

void SceneGraph::SetMainCamera(Camera* cam) {
	m_mainCamera = cam;
}

Camera& SceneGraph::GetMainCamera() {
	return *m_mainCamera;
}