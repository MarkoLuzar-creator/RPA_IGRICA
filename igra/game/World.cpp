#include "World.h"
#include <iostream>
#include <MiniMap.h>

World::World(const char* level){
	_level = level;
}

void World::Push(const char* file, int x, int y, int w, int h, float s, SDL_Renderer& r, SDL_RendererFlip f){
	Tile a;
	a._texture = new TextureComponent(file, x, y, w, h, &r, s, f);
	_vect.push_back(a);
}

void World::Draw(){
	for (std::vector<Tile>::iterator it = _vect.begin(); it != _vect.end(); it++) {
		if (_level == Level::GetInstance().GetCurrentLevelName()) {
			it->_texture->DrawD();
		}
		else {
			break;
		}
	}
}

void World::Update(){
	if (_level == Level::GetInstance().GetCurrentLevelName()) {
		if (init) {
			MiniMap::GetInstance().LoadWorld(*this);
			init = false;
		}
	}
}

std::vector<Tile>& World::GetVect(){
	return _vect;
}
