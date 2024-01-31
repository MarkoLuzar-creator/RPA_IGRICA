#pragma once
#include <SDL.h>
#include <string>
#include "../CORE/TextureComponent.h"


class Ozadje{
public:
	Ozadje(const char* texture, const char* level, int x, int y, int w, int h, float s, SDL_Renderer* r, SDL_RendererFlip f);
	void Update();
private:
	const char* _level;
	TextureComponent* _texture;
};

