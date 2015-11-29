#include "GameEngine.h"

#include <GL/glew.h>
#include <GLM/glm.hpp>

#include "LogManager.h"

void GameEngine::Run() {
	Initialize();

	int frameTicks = 0, lastTicks = 0;

	// Game Loop
	while (m_state != GameState::EXIT) {
		// Get time at start of frame
		lastTicks = frameTicks;
		frameTicks = (int)SDL_GetTicks();

		Update();
		Prerender();
		Render();
		Postrender();

		// TODO: Implement frame limiting with Clock & Timer, OR implement SDL_GetTicks into Clock & Timer instead of Windows functions
		// Limit FPS
		float desiredFPS = 1000.0F / 60.0F;
		float endTicks = (float)SDL_GetTicks() - frameTicks;
		if (desiredFPS > endTicks)
			SDL_Delay((Uint32)(desiredFPS - endTicks));
	}

	// Shutdown procedure
	if (m_scene)
		delete m_scene;
	if (m_renderer)
		delete m_renderer;
	SDL_Quit();
}

void GameEngine::Exit() {
	m_state = GameState::EXIT;
}

void GameEngine::Initialize() {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		LogManager::getInstance().logFatal("Failed to initialize SDL: " + std::string(SDL_GetError()));

	GLfloat windowWidth = 800;
	GLfloat windowHeight = 600;
	// Create an SDL window with OpenGL enabled
	m_window = SDL_CreateWindow("Game Engine Assignment", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (m_window == nullptr)
		LogManager::getInstance().logFatal("SDL window could not be created.");

	// Create the OpenGL context
	SDL_GLContext context = SDL_GL_CreateContext(m_window);
	if (context == nullptr)
		LogManager::getInstance().logFatal("SDL GL context could not be created.");

	// Check the OpenGL version
	LogManager::getInstance().logInfo("***   OpenGL Version: " + std::string((const char*)glGetString(GL_VERSION)) + "   ***\n");

	// Set the background color to black (default)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Enable vsync
	SDL_GL_SetSwapInterval(0);
	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	// Enable alpha blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create the renderer and initialize the shader program
	m_renderer = new OpenGLRenderer();
	m_renderer->InitShaders("shaders/shader.vert", "shaders/shader.frag");
	// Create the main camera
	m_camera = new Camera(windowWidth, windowHeight);
	// Create the scene graph and give it a pointer to the main camera
	m_scene = new SceneGraph();
	m_scene->SetMainCamera(m_camera);
}

void GameEngine::Prerender() {
	glClearDepth(1.0); // Set depth to 1.0  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffer
}

void GameEngine::Postrender() {
	SDL_GL_SwapWindow(m_window);
}

void GameEngine::Add(GameObject* gameObject, GameObject* parent) {
	if (parent) {
		parent->AddChild(gameObject);
	} else
		m_scene->Add(gameObject);
}

void GameEngine::Remove(GameObject* gameObject) {
	gameObject->GetParent()->RemoveChild(gameObject);
}

void GameEngine::ResizeWindow(GLfloat newWidth, GLfloat newHeight) {
	m_camera->ResizeWindow(newWidth, newHeight);
}

const GLfloat& GameEngine::GetWindowWidth() {
	return m_camera->GetWindowWidth();
}

const GLfloat& GameEngine::GetWindowHeight() {
	return m_camera->GetWindowHeight();
}