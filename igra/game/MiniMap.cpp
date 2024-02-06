#include "MiniMap.h"
#include <iostream>
#include <Player.h>
#include <Igra.h>


bool toggle = 0;

void MiniMap::Draw(){
    if ("menu" != Level::GetInstance().GetCurrentLevelName() && "options" != Level::GetInstance().GetCurrentLevelName() && toggle) {
        _texture->DrawS();

        for (std::vector<Tile>::iterator it = _world->GetVect().begin(); it != _world->GetVect().end(); it++) {
            LegacyTexture::GetInstance().CreateTexture(it->_texture->_filePath);
            LegacyTexture::GetInstance().DrawS(it->_texture->_filePath, _texture->_position.m_X + it->_texture->_position.m_X / m_MapScale + 10,
             _texture->_position.m_Y + it->_texture->_position.m_Y / m_MapScale + 10, 1920, 1920, &Window::GetInstance().GetRenderer(), 0.02, SDL_FLIP_NONE);
        }


        if (Player::GetInstance().GetOrigin().GetDistance(_lab->GetIndexLab()._texture->_position) < WorldSettings::viewDistance) {
            LegacyTexture::GetInstance().CreateTexture(_lab->GetIndexLab()._texture->_filePath);
            LegacyTexture::GetInstance().DrawS(_lab->GetIndexLab()._texture->_filePath, _texture->_position.m_X + _lab->GetIndexLab()._texture->_position.m_X / m_MapScale, _texture->_position.m_Y + _lab->GetIndexLab()._texture->_position.m_Y / m_MapScale, _lab->GetIndexLab()._texture->_size.m_X, _lab->GetIndexLab()._texture->_size.m_Y, &Window::GetInstance().GetRenderer(), 0.015, SDL_FLIP_NONE);
        }
             
        for (std::vector<E>::iterator it = _enemy->GetVect().begin(); it != _enemy->GetVect().end(); it++) {
            if (Player::GetInstance().GetOrigin().GetDistance(it->_animation->_texture->_position) < WorldSettings::viewDistance) {
                LegacyTexture::GetInstance().CreateTexture("../assets/nasprotnik.png");
                LegacyTexture::GetInstance().DrawS("../assets/nasprotnik.png", _texture->_position.m_X + it->_animation->_texture->_position.m_X / m_MapScale, _texture->_position.m_Y + it->_animation->_texture->_position.m_Y / m_MapScale, 1920, 1920, &Window::GetInstance().GetRenderer(), 0.005, SDL_FLIP_NONE);
            }
        }
        LegacyTexture::GetInstance().CreateTexture("../assets/player.png");
        LegacyTexture::GetInstance().DrawS("../assets/player.png", _texture->_position.m_X + Player::GetInstance().GetOrigin().m_X / m_MapScale, _texture->_position.m_Y + Player::GetInstance().GetOrigin().m_Y / m_MapScale, 1920, 1920, &Window::GetInstance().GetRenderer(), 0.005, SDL_FLIP_NONE);
    }
}

void MiniMap::LoadLab(Lab& l){
    _lab = &l;
    _texture = new TextureComponent("../assets/miniMap.png", 1920 / 2 - 500 / 2, 1080 / 2 - 500 / 2, 500, 500, &Window::GetInstance().GetRenderer(), 1.0f, SDL_FLIP_NONE);
}

void MiniMap::LoadEnemy(Enemy& e){
    _enemy = &e;
}

void MiniMap::LoadWorld(World& w){
    _world = &w;
}

void MiniMap::Update(){
    if (Input::GetInstance().GetKeyPressed(SDL_SCANCODE_M)) {
        toggle = !toggle;
    }
}