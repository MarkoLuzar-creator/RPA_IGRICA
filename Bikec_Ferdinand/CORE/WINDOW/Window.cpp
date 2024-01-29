#include "Window.h"
#include <fstream>
#include <iostream>
#include "../TEXTURE/Texture.h"

const std::string ASSETSMANAGER = "../../Asset_Manager.txt";
const std::string DEFAULTASSETPATH = "../Assets/";
const std::string LEVELMANAGER = "../../Level_Manager.txt";
const std::string DEFAULTLEVELPATH = "../Levels/";

void Window::CreateWindow(int width, int height, int posX, int posY){
	m_Size = new Vector2D(width, height);
	m_Scale = new Vector2D(1, 1);

	m_Window = SDL_CreateWindow("Made with Puddle engine", posX, posY, m_Size->m_X, m_Size->m_Y, 0);
	if (m_Window == nullptr) {
		std::cout << SDL_GetError() << std::endl;
	}
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) {
		std::cout << SDL_GetError() << std::endl;
	}
}

void Window::DestroyWindow(){
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
}

Vector2D Window::GetScaleSize(int width, int height) {
	Vector2D scale;
	scale.m_X = m_Scale->m_X * width;
	scale.m_Y = m_Scale->m_Y * height;
	return scale;
}

Vector2D Window::GetScalePosition(int x, int y, int width, int height, Vector2D offset) {
	Vector2D scale;
	scale.m_X = x * m_Scale->m_X;
	scale.m_Y = y * m_Scale->m_Y;

	scale.m_X = scale.m_X - (m_Scale->m_X * width / 2);
	scale.m_Y = scale.m_Y - (m_Scale->m_Y * height / 2);

	scale.m_X -= offset.m_X * m_Scale->m_X - m_Size->m_X / 2;
	scale.m_Y -= offset.m_Y * m_Scale->m_Y - m_Size->m_Y / 2;
	return scale;
}

void Window::WindowClear() {
	m_Scale = new Vector2D((float)m_Size->m_X / 1920, (float)m_Size->m_Y / 1080);
	SDL_SetRenderDrawColor(m_Renderer, 255, 140, 0, 255);
	SDL_RenderClear(m_Renderer);
}

void Window::WindowRender() {
	SDL_RenderPresent(m_Renderer);
}

SDL_Window& Window::GetWindow() {
	return *m_Window;
}

SDL_Renderer& Window::GetRenderer() {
	return *m_Renderer;
}


Vector2D& Window::GetSize() {
	return *m_Size;
}


void Window::SetSize(int width, int height) {
	delete m_Size;
	m_Size = new Vector2D(width, height);
}