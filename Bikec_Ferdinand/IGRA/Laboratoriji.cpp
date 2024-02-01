#include "Laboratoriji.h"
#include "../CORE/LEVEL/Level.h"
#include "../IGRA/Igralec.h"
#include <iostream>


void Laboratoriji::Init(){
    for (int i = 0; i < 15; i++) {
        int x = rand() % (2 * (int)MiniMap::worldSize) - MiniMap::worldSize;
        int y = rand() % (2 * (int)MiniMap::worldSize) - MiniMap::worldSize;

        struct El t;
        t._texture = new TextureComponent("../Assets/arena.png", x, y, 1152, 1152, &Window::GetInstance().GetRenderer(), 1.0f, SDL_FLIP_NONE);
        t._level = "level1";

        bool overlap = false;
        for (El& i : _list) {
            if (SDL_HasIntersection(&i._texture->_hitbox, &t._texture->_hitbox)) {
                overlap = true;
                break;
            }
        }
        if (!overlap) {
            t._indexElementa = i;
            _list.push_back(t);
        }
    }
}

void Laboratoriji::Draw() {
    for (El& i : _list) {
        if (i._level == Level::GetInstance().GetCurrentLevelName()) {
            if (i._indexElementa == _indexPrikazanegaElementa) {
                i._texture->DrawD();
            }
        }
    }
    std::cout << _list.size();
}

void Laboratoriji::Update() {
    for (El& i : _list) {
        if (i._level == Level::GetInstance().GetCurrentLevelName()) {
            if (SDL_HasIntersection(&Igralec::GetInstance().GetHitBox(), &i._texture->_hitbox)) {
                if (_indexPrikazanegaElementa == i._indexElementa && i._indexElementa < _list.size() - 1) {
                    _indexPrikazanegaElementa++;
                }
            }
        }
    }
}

void Laboratoriji::Clear(const char* level){
    auto it = std::remove_if(_list.begin(), _list.end(), [level](const El& i) {
        return i._level == level;
    });

    _list.erase(it, _list.end());
}
