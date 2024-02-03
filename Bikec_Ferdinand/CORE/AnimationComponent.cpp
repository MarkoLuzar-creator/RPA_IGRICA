#include "AnimationComponent.h"
#include "../CORE/WINDOW/Window.h"
#include "../CORE/CAMERA/Camera.h"

AnimationComponent::AnimationComponent(const char* filePath, int x, int y, int w, int h, int row, int frames, int speed, float scale, SDL_Renderer* r, SDL_RendererFlip flip){
	_texture = new TextureComponent(filePath, x, y, w, h, r, scale, flip);
	_row = row;
	_frames = frames;
	_speed = speed;
	_spriteFrame = 0;
}

void AnimationComponent::Update(){
	_spriteFrame = (SDL_GetTicks() / _speed) % _frames;
}

void AnimationComponent::DrawD(){
	Vector2D offset = Camera::GetInstance().GetPosition();
	Vector2D pos = Window::GetInstance().GetScalePosition(_texture->_position.m_X, _texture->_position.m_Y, _texture->_size.m_X * _texture->_scale, _texture->_size.m_Y * _texture->_scale, offset);
	Vector2D size = Window::GetInstance().GetScaleSize(_texture->_size.m_X * _texture->_scale, _texture->_size.m_Y * _texture->_scale);

	SDL_Rect srcRect = { _texture->_size.m_X * _spriteFrame, _texture->_size.m_Y * _row, _texture->_size.m_X, _texture->_size.m_Y };
	SDL_Rect destRect = { pos.m_X, pos.m_Y, size.m_X, size.m_Y };
	SDL_RenderCopyEx(_texture->_renderer, _texture->_texture, &srcRect, &destRect, 0, nullptr, _texture->_flip);
	SDL_Rect hitbox = { pos.m_X, pos.m_Y, size.m_X, size.m_Y };
	_texture->_hitbox = hitbox;
}

void AnimationComponent::DrawS(){
	Vector2D offset;
	Vector2D pos = Window::GetInstance().GetScalePosition(_texture->_position.m_X, _texture->_position.m_Y, _texture->_size.m_X * _texture->_scale, _texture->_size.m_Y * _texture->_scale, offset);
	Vector2D size = Window::GetInstance().GetScaleSize(_texture->_size.m_X * _texture->_scale, _texture->_size.m_Y * _texture->_scale);

	SDL_Rect srcRect = { _texture->_size.m_X * _spriteFrame, _texture->_size.m_Y * _row, _texture->_size.m_X, _texture->_size.m_Y };
	SDL_Rect destRect = { pos.m_X, pos.m_Y, size.m_X, size.m_Y };
	SDL_RenderCopyEx(_texture->_renderer, _texture->_texture, &srcRect, &destRect, 0, nullptr, _texture->_flip);
	SDL_Rect hitbox = { pos.m_X, pos.m_Y, size.m_X, size.m_Y };
	_texture->_hitbox = hitbox;
}
