#pragma once
#include <SDL.h>
#include "Vector2D.h"

class Input{
public:
	static Input& GetInstance() {
		static Input instance;
		return instance;
	}
	void UpdateKeys();
	void UpdateMousePosition();
	void UpdateMouseClicks();
	bool GetKeyDown(SDL_Scancode key);
	bool GetMouseClick(int SDL_CLICK);
	bool GetKeyPressed(SDL_Scancode key);
	Vector2D& GetMousePosition();
private:
	Input(){}
	const Uint8* m_KeyStates = SDL_GetKeyboardState(nullptr);
	Uint8 m_MouseStates = SDL_GetMouseState(nullptr, nullptr);
	Vector2D m_MousePosition;
	SDL_Scancode m_LastKeyPressed = SDL_SCANCODE_UNKNOWN;
};

