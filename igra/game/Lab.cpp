#include "Lab.h"
#include <iostream>
#include <Player.h>

Lab::Lab(const char* level){
    _level = level;
    _index = 0;
}

void Lab::Push(const char* file, int x, int y, int w, int h, float s, SDL_Renderer& r, SDL_RendererFlip f){
    L a;
    a._texture = new TextureComponent(file, x, y, w, h, &r, s, f);

    bool overlap = false;
    for (std::vector<L>::iterator it = _vect.begin(); it != _vect.end(); it++) {
        if (SDL_HasIntersection(&it->_texture->_hitbox, &a._texture->_hitbox)) {
            overlap = true;
            break;
        }
    }

    if (!overlap) {
        int i = 0;
        for (std::vector<L>::iterator it = _vect.begin(); it != _vect.end(); it++, i++) {}
        a._index = i;
        _vect.push_back(a);
    }
}

void Lab::Draw(){
    if (_level == Level::GetInstance().GetCurrentLevelName()) {
        _vect.at(_index)._texture->DrawD();
    }
}

void Lab::Update(){
    if (_level == Level::GetInstance().GetCurrentLevelName() && _index < _vect.size() - 1) {
        if (SDL_HasIntersection(&Player::GetInstance().GetHitBox(), &_vect.at(_index)._texture->_hitbox)) {
            _index++;
            Camera::GetInstance().SetTargetReturn(_vect[_index]._texture->_position, Player::GetInstance().GetOrigin());
            //Camera::GetInstance().SetTarget(_vect[_index]._texture->_position);
        }
    }
}

const char* Lab::GetLevel(){
    return _level;
}

L& Lab::GetIndexLab(){
    return _vect[_index];
}

void Lab::Clear(){
    _vect.clear();
}
