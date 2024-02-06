#include "TextureComponent.h"
#include <SDL_image.h>
#include <iostream>
#include "Camera.h"
#include "Window.h"


TextureComponent::TextureComponent(const char* filePath, int x, int y, int w, int h, SDL_Renderer* renderer, float scale, SDL_RendererFlip f){
	SDL_Surface* surface = IMG_Load(filePath);
	if (surface == nullptr) {
		std::cout << "Surface error: " << SDL_GetError() << std::endl;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr) {
		std::cout << "Texture error: " << SDL_GetError() << std::endl;
	}
	_position = Vector2D(x, y);
	_size = Vector2D(w, h);
	_texture = texture;
	_renderer = renderer;
	_flip = f;
	_scale = scale;
	SDL_Rect hitbox = { _position.m_X, _position.m_Y, _size.m_X, _size.m_Y };
	_hitbox = hitbox;
	_filePath = filePath;
}

TextureComponent::TextureComponent(const TextureComponent& c){
	*this = c;
}

void TextureComponent::DrawS(){
	Vector2D offset;
	Vector2D pos = Window::GetInstance().GetScalePosition(_position.m_X, _position.m_Y, _size.m_X * _scale, _size.m_Y * _scale, offset);
	Vector2D size = Window::GetInstance().GetScaleSize(_size.m_X * _scale, _size.m_Y * _scale);

	SDL_Rect srcRect = { 0, 0, _size.m_X, _size.m_Y };
	SDL_Rect destRect = { pos.m_X, pos.m_Y, size.m_X, size.m_Y };
	SDL_RenderCopyEx(_renderer, _texture, &srcRect, &destRect, 0, nullptr, _flip);
	SDL_Rect hitbox = { pos.m_X, pos.m_Y, size.m_X, size.m_Y };
	_hitbox = hitbox;
}

void TextureComponent::DrawD(){
	Vector2D offset = Camera::GetInstance().GetPosition();
	Vector2D pos = Window::GetInstance().GetScalePosition(_position.m_X, _position.m_Y, _size.m_X * _scale, _size.m_Y * _scale, offset);
	Vector2D size = Window::GetInstance().GetScaleSize(_size.m_X * _scale, _size.m_Y * _scale);

	SDL_Rect srcRect = { 0, 0, _size.m_X, _size.m_Y };
	SDL_Rect destRect = { pos.m_X, pos.m_Y, size.m_X, size.m_Y };
	SDL_RenderCopyEx(_renderer, _texture, &srcRect, &destRect, 0, nullptr, _flip);
	SDL_Rect hitbox = { pos.m_X, pos.m_Y, size.m_X, size.m_Y };
	_hitbox = hitbox;
}


void LegacyTexture::CreateTexture(const char* filePath){
	if (m_TextureMap[filePath] == nullptr) {
		SDL_Surface* surface = IMG_Load(filePath);
		if (surface == nullptr) {
			std::cout << SDL_GetError() << ": Wrong File Path" << std::endl;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(&Window::GetInstance().GetRenderer(), surface);
		if (texture == nullptr) {
			std::cout << SDL_GetError() << ": Failed To Create Texture" << std::endl;
		}
		m_TextureMap[filePath] = texture;
		std::cout << "lol";
	}
}

void LegacyTexture::DrawS(const char* filePath, int x, int y, int width, int height, SDL_Renderer* renderer, float scale, SDL_RendererFlip f){
	Vector2D offset;
	Vector2D pos = Window::GetInstance().GetScalePosition(x, y, width * scale, height * scale, offset);
	Vector2D size = Window::GetInstance().GetScaleSize(width * scale, height * scale);

	SDL_Rect srcRect = { 0, 0, width, height };
	SDL_Rect destRect = { pos.m_X, pos.m_Y, size.m_X, size.m_Y };
	SDL_RenderCopyEx(&Window::GetInstance().GetRenderer(), m_TextureMap[filePath], &srcRect, &destRect, 0, nullptr, f);
}
