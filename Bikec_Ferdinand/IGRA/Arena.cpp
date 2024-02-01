#include "Arena.h"
#include "../CORE/LEVEL/Level.h"
#include "../IGRA/Igralec.h"
#include <iostream>

int Arena::m_ArenaIndex = 0;
int Arena::_steviloAren = 0;
std::vector<Arena> Arena::_arene;

Arena::Arena(const char* texture, const char* level, int x, int y, int w, int h, float s, SDL_Renderer* r, SDL_RendererFlip f) {
    _texture = new TextureComponent(texture, x, y, w, h, r, s, f);
    _pushanIndex = NULL;
    _level = level;

    bool overlap = false;
    for (Arena& i : _arene) {
        if (SDL_HasIntersection(&i._texture->_hitbox, &_texture->_hitbox) && level == i._level) {
            overlap = true;
            break;
        }
    }

    if (!overlap) {
        _pushanIndex = _steviloAren;
        _steviloAren++;
        _arene.push_back(*this);
    }
}

void Arena::Draw() {
    if (_level == Level::GetInstance().GetCurrentLevelName()) {
        if (m_ArenaIndex == _pushanIndex) {
            _texture->DrawD();
        }
    }
}

void Arena::Update() {
    if (SDL_HasIntersection(&Igralec::GetInstance().GetHitBox(), &_texture->_hitbox) && _pushanIndex == m_ArenaIndex && m_ArenaIndex < _arene.size() - 1) {
            m_ArenaIndex++;
    }
}
