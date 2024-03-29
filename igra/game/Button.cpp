﻿#include "Button.h"
#include <iostream>


Button::Button(const char* baseTexturePath, const char* hoverTexturePath, const char* level, int x, int y, int w, int h, float scale, SDL_Renderer* r, SDL_RendererFlip flip, ButtonTypes buttonType){
	_baseTexture = new TextureComponent(hoverTexturePath, x, y, w, h, r, scale, flip);
	_hoverTexture = new TextureComponent(hoverTexturePath, x, y, w, h, r, scale, flip);
	_buttonType = buttonType;
	_level = level;
}

void Button::DrawBase(){
	if (_level == Level::GetInstance().GetCurrentLevelName()) {
		_baseTexture->DrawD();
	}
}

void Button::DrawHover(){
	if (_level == Level::GetInstance().GetCurrentLevelName()) {
		SDL_Rect button = _baseTexture->_hitbox;
		SDL_Rect mouse = { Input::GetInstance().GetMousePosition().m_X, Input::GetInstance().GetMousePosition().m_Y, 1, 1 };
		if (SDL_HasIntersection(&mouse, &button)) {
			_hoverTexture->DrawD();
		}
	}
}

void Button::Update(){
	if (_level == Level::GetInstance().GetCurrentLevelName()) {

		SDL_Rect button = _baseTexture->_hitbox;
		SDL_Rect mouse = { Input::GetInstance().GetMousePosition().m_X, Input::GetInstance().GetMousePosition().m_Y, 1, 1};

		if (Input::GetInstance().GetMouseClick(SDL_BUTTON_LEFT) && SDL_HasIntersection(&mouse, &button)) {
			switch (_buttonType) {
			case ButtonTypes::Play: Level::GetInstance().NextLevel(); break;
			case ButtonTypes::Exit: exit(0); break;
			case ButtonTypes::Options: Level::GetInstance().SetLevel("options"); break;
			case ButtonTypes::Home: Level::GetInstance().SetLevel("menu"); break;
			}
			Input::GetInstance().UpdateMouseClicks();
		}
	}
}
