#pragma once
#include <SDL.h>
#include <string>
#include <engine.h>


class Sprite{
public:
	Sprite(const char* texture, const char* level, int x, int y, int w, int h, float s, SDL_Renderer* r, SDL_RendererFlip f);
	void Draw();
	void Update();
private:
	const char* _level;
	TextureComponent* _texture;
};

