#include "TextureComponent.h"
#include <SDL_image.h>
#include <iostream>
#include "CAMERA/Camera.h"


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
}

void TextureComponent::DrawS(){
	Vector2D offset;
	Vector2D pos = Window::GetInstance().GetScalePosition(_position.m_X, _position.m_Y, _size.m_X * _scale, _size.m_Y * _scale, offset);
	Vector2D size = Window::GetInstance().GetScaleSize(_size.m_X * _scale, _size.m_Y * _scale);

	SDL_Rect srcRect = { 0, 0, _size.m_X, _size.m_Y };
	SDL_Rect destRect = { pos.m_X, pos.m_Y, size.m_X, size.m_Y };
	SDL_RenderCopyEx(_renderer, _texture, &srcRect, &destRect, 0, nullptr, _flip);
}

void TextureComponent::DrawD(){
	Vector2D offset = Camera::GetInstance().GetPosition();
	Vector2D pos = Window::GetInstance().GetScalePosition(_position.m_X, _position.m_Y, _size.m_X * _scale, _size.m_Y * _scale, offset);
	Vector2D size = Window::GetInstance().GetScaleSize(_size.m_X * _scale, _size.m_Y * _scale);

	SDL_Rect srcRect = { 0, 0, _size.m_X, _size.m_Y };
	SDL_Rect destRect = { pos.m_X, pos.m_Y, size.m_X, size.m_Y };
	SDL_RenderCopyEx(_renderer, _texture, &srcRect, &destRect, 0, nullptr, _flip);
}
