#pragma once
#include <SDL/SDL.h>
#include <GLM/glm.hpp>
#include <unordered_map>

// The class that handles mouse and keyboard input
class InputManager {
public:
	// Get (and create) the InputManager instance
	static InputManager* GetInstance();
	// Deletes the input manager and the pointer to it
	void DestroyInputManager(InputManager*&);

	// Updates the keyboard and mouse states
	int Update(SDL_Event&);

	/// Keyboard functions
	bool KeyDown(Uint32); // Checks if a key is held down
	bool KeyUp(Uint32); // Checks if a key is up (released)
	bool KeyPress(Uint32); // Checks if a key has been pressed (but not held)

	/// Mouse functions
	bool MouseButtonDown(Uint8); // If a button is held
	bool MouseButtonUp(Uint8); // If a button is up
	bool MouseButtonPress(Uint8); // If a button is pressed
	bool GetMouseMoved(); // If the mouse has moved since last frame
	glm::vec2 GetMousePos(); // The mouse's current position
private:
	static InputManager* instance;

	std::unordered_map<Uint32, bool> currentKeyStates;
	std::unordered_map<Uint32, bool> previousKeyStates;
	bool previousMButtonStates[5];
	bool currentMButtonStates[5];
	glm::vec2 currentMousePos;
	bool mouseMoved = false;

	InputManager(); // Private constructor for singleton class
  ~InputManager() {}
};