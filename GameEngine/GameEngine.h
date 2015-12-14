#pragma once
#include <SDL/SDL.h>
#include "ResourceManager.h"
#include "InputManager.h"
#include "OpenGLRenderer.h"
#include "SceneGraph.h"
#include "GameTime.h"

enum class GameState { PLAY, EXIT };

class GameEngine {
public:
	void Run();
protected:
	ResourceManager* m_resources;
	InputManager* m_input;
	OpenGLRenderer* m_renderer;
	SceneGraph* m_scene;
	Camera* m_mainCamera;

	virtual void Initialize() = 0;
	virtual void Update(GameTime&) = 0;
	virtual void Prerender();
	virtual void Render() = 0;
	virtual void Postrender();

	const GLfloat& GetWindowWidth();
	const GLfloat& GetWindowHeight();

	void Add(GameObject* gameObject, GameObject* parent = nullptr);
	void Remove(GameObject* gameObject);
	
	void ResizeWindow(GLfloat newWidth, GLfloat newHeight);
	void Exit();
private:
	SDL_Window* m_window;

	GameState m_state;
};