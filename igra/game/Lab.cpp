#include "Lab.h"
#include <iostream>
#include <Player.h>
#include <MiniMap.h>

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
        std::string num = std::to_string(_vect.size() - _index - 1);
        std::string msg = "stevilo aren: " + num;
        TTFText::GetInstance().RenderText(msg.c_str(), 10, 140, "../assets/font.ttf", 60);
    }
}


void Lab::Update(){
    if (_level == Level::GetInstance().GetCurrentLevelName() && _index < _vect.size() - 1) {
        if (init) {
            MiniMap::GetInstance().LoadLab(*this);
            init = false;
        }
        if (SDL_HasIntersection(&Player::GetInstance().GetHitBox(), &_vect.at(_index)._texture->_hitbox)) {
            _index++;
            if (_index != _vect.size() - 1)
                Camera::GetInstance().SetAnimationTarget(_vect[_index]._texture->_position);
            else Level::GetInstance().NextLevel();
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
