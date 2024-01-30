#pragma once
#include <SDL.h>
#include "PHYSICS/Vector2D.h"

class TextureComponent{
public:
	TextureComponent(const char* filePath, int x, int y, int w, int h, SDL_Renderer* renderer, float scale, SDL_RendererFlip f);
	void DrawS();
	void DrawD();
	float _scale;
	Vector2D _position, _size;
	SDL_RendererFlip _flip;
	SDL_Rect _hitbox;
private:
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
};

