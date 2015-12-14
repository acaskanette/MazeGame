#include "InputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager* InputManager::GetInstance() {
	if (instance == nullptr)
		instance = new InputManager();

	return instance;
}

void InputManager::DestroyInputManager(InputManager*& inputManagerPointer) {
	if (instance) {
		delete instance;
		instance = nullptr;
		inputManagerPointer = nullptr;
	}
}

InputManager::InputManager() {
	std::fill(previousMButtonStates, previousMButtonStates + 5, false);
	std::fill(currentMButtonStates, currentMButtonStates + 5, false);
	currentMousePos = glm::vec2(0.0f);
	mouseMoved = false;
}

int InputManager::Update(SDL_Event& inputEvent) {
	// Set the previous frame states
	for (auto& it : currentKeyStates)
		previousKeyStates[it.first] = it.second;
	for (int i = 0; i < 5; i++)
    previousMButtonStates[i] = currentMButtonStates[i];
	mouseMoved = false;

	while (SDL_PollEvent(&inputEvent)) {
		if (inputEvent.type == SDL_QUIT)
			return 1; // Send exit command to game
		else if (inputEvent.type == SDL_WINDOWEVENT && inputEvent.window.event == SDL_WINDOWEVENT_RESIZED)
			return 2; // Send window resize command to game

		// Set key states
		SDL_Keycode key = inputEvent.key.keysym.sym;
		if (inputEvent.type == SDL_KEYDOWN)
			currentKeyStates[key] = true;
		if (inputEvent.type == SDL_KEYUP)
			currentKeyStates[key] = false;

		// Set mouse button states
		if (inputEvent.type == SDL_MOUSEBUTTONDOWN)
			currentMButtonStates[inputEvent.button.button - 1] = true;
		if (inputEvent.type == SDL_MOUSEBUTTONUP)
			currentMButtonStates[inputEvent.button.button - 1] = false;

		// Set mouse position
		if (inputEvent.type == SDL_MOUSEMOTION) {
			mouseMoved = true;

			currentMousePos.x = (float)inputEvent.motion.x;
			currentMousePos.y = (float)inputEvent.motion.y;
		}
	}

	return 0;
}

bool InputManager::KeyDown(Uint32 key) {
	return currentKeyStates[key];
}

bool InputManager::KeyUp(Uint32 key) {
	return !currentKeyStates[key];
}

bool InputManager::KeyPress(Uint32 key) {
	return previousKeyStates[key] && !currentKeyStates[key];
}

bool InputManager::MouseButtonDown(Uint8 button) {
	return currentMButtonStates[button - 1];
}

bool InputManager::MouseButtonUp(Uint8 button) {
	return !currentMButtonStates[button - 1];
}

bool InputManager::MouseButtonPress(Uint8 button) {
	return previousMButtonStates[button - 1] && !currentMButtonStates[button - 1]; 
}

bool InputManager::GetMouseMoved() {
	return mouseMoved;
}

glm::vec2 InputManager::GetMousePos() {
	return currentMousePos;
}