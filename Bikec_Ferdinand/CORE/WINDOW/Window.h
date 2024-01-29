#pragma once
#include <SDL.h>
#include <map>
#include <string>
#include "../PHYSICS/Vector2D.h"

class Window {
public:
	static Window& GetInstance() {
		static Window instance;
		return instance;
	}
	void CreateWindow(int width, int height, int posX, int posY);
	void DestroyWindow();
	Vector2D GetScaleSize(int width, int height);
	Vector2D GetScalePosition(int x, int y, int width, int height, Vector2D offset);
	void SetSize(int width, int height);
	void WindowClear();
	void WindowRender();

	SDL_Window& GetWindow();
	SDL_Renderer& GetRenderer();
	Vector2D& GetSize();

private:
	Window() {}
	Vector2D* m_Size = nullptr;
	Vector2D* m_Scale = nullptr;
	SDL_Window* m_Window = nullptr;
	SDL_Renderer* m_Renderer = nullptr;
};



