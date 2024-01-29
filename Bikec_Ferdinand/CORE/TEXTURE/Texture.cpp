#include "Texture.h"
#include <iostream>
#include <SDL_image.h>
#include "../CAMERA/Camera.h"

void Texture::Load(std::string id, std::string fileName){
	SDL_Surface* surface = IMG_Load(fileName.c_str());
	if (surface == nullptr) {
		std::cout << SDL_GetError() << ": Wrong File Path" << std::endl;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(&Window::GetInstance().GetRenderer(), surface);
	if (texture == nullptr) {
		std::cout << SDL_GetError() << ": Failed To Create Texture" << std::endl;
	}
	m_TextureMap[id] = texture;
}

void Texture::DrawDynamic(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip, float scale){
	Vector2D offset = Camera::GetInstance().GetPosition();
	Vector2D pos = Window::GetInstance().GetScalePosition(x, y, width * scale, height * scale, offset);
	Vector2D size = Window::GetInstance().GetScaleSize(width * scale, height * scale);

	SDL_Rect srcRect = { 0, 0, width, height };
	SDL_Rect destRect = { pos.m_X, pos.m_Y, size.m_X, size.m_Y };
	SDL_RenderCopyEx(&Window::GetInstance().GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void Texture::DrawStatic(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip, float scale){
	Vector2D offset;
	Vector2D pos = Window::GetInstance().GetScalePosition(x, y, width * scale, height * scale, offset);
	Vector2D size = Window::GetInstance().GetScaleSize(width * scale, height * scale);

	SDL_Rect srcRect = { 0, 0, width, height };
	SDL_Rect destRect = { pos.m_X, pos.m_Y, size.m_X, size.m_Y };
	SDL_RenderCopyEx(&Window::GetInstance().GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void Texture::DrawFrameDynamic(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip, float scale){
	Vector2D offset;
	Vector2D pos = Window::GetInstance().GetScalePosition(x, y, width * scale, height * scale, offset);
	Vector2D size = Window::GetInstance().GetScaleSize(width * scale, height * scale);

	SDL_Rect srcRect = { width * frame, height * row, width, height };
	SDL_Rect destRect = { pos.m_X, pos.m_Y, size.m_X, size.m_Y };
	SDL_RenderCopyEx(&Window::GetInstance().GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void Texture::DrawFrameStatic(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip, float scale){
	Vector2D offset = Camera::GetInstance().GetPosition();
	Vector2D pos = Window::GetInstance().GetScalePosition(x, y, width * scale, height * scale, offset);
	Vector2D size = Window::GetInstance().GetScaleSize(width * scale, height * scale);

	SDL_Rect srcRect = { width * frame, height * row, width, height };
	SDL_Rect destRect = { pos.m_X, pos.m_Y, size.m_X, size.m_Y };
	SDL_RenderCopyEx(&Window::GetInstance().GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}