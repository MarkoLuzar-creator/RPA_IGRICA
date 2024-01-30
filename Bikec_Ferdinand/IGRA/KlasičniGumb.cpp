#include "KlasičniGumb.h"
#include "../CORE/TEXTURE/Texture.h"
#include "../CORE/VECTOR/Vector.h"
#include "../CORE/LEVEL/Level.h"
#include "../CORE/INPUT/Input.h"
#include "../CORE/CAMERA/Camera.h"
#include "Igralec.h"
#include <iostream>


KlasičniGumb::KlasičniGumb(const char* baseTexturePath, const char* hoverTexturePath, int x, int y, int w, int h, float scale, SDL_Renderer* r, SDL_RendererFlip flip, ButtonTypes buttonType){
	_baseTexture = new TextureComponent(hoverTexturePath, x, y, w, h, r, scale, flip);
	_hoverTexture = new TextureComponent(hoverTexturePath, x, y, w, h, r, scale, flip);
	_buttonType = buttonType;
}

void KlasičniGumb::Draw(){
	if ("menu" == Level::GetInstance().GetCurrentLevelName()) {
		_baseTexture->DrawD();
	}
}

void KlasičniGumb::Update(){
	if ("menu" == Level::GetInstance().GetCurrentLevelName()) {


		SDL_Rect button = _baseTexture->_hitbox;
		SDL_Rect mouse = { Input::GetInstance().GetMousePosition().m_X, Input::GetInstance().GetMousePosition().m_Y, 1, 1};

		if (SDL_HasIntersection(&mouse, &button)) {
			_hoverTexture->DrawD();

			if (Input::GetInstance().GetMouseClick(SDL_BUTTON_LEFT)) {
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
}
