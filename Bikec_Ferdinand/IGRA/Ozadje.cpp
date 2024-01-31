#include "Ozadje.h"
#include "../CORE/LEVEL/Level.h"


Ozadje::Ozadje(const char* texture, const char* level, int x, int y, int w, int h, float s, SDL_Renderer* r, SDL_RendererFlip f){
	_texture = new TextureComponent(texture, x, y, w, h, r, s, f);
	_level = level;
}

void Ozadje::Update(){
	if (_level == Level::GetInstance().GetCurrentLevelName()) {
		_texture->DrawD();
	}
}
