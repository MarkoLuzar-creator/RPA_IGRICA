﻿#pragma once
#include <SDL.h>
#include "../CORE/TextureComponent.h"

enum class ButtonTypes {
	Play,
	Exit,
	Options,
	Resolution,
	Home,
};

class Button{
public:
	Button(const char* baseTexturePath, const char* hoverTexturePath, const char* level, int x, int y, int w, int h, float scale,  SDL_Renderer* r, SDL_RendererFlip flip, ButtonTypes buttonType);
	void Draw();
	void Update();
private:
	ButtonTypes _buttonType;
	TextureComponent *_baseTexture, *_hoverTexture;
	const char* _level;
};
