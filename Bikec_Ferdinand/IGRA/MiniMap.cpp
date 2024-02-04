#include "MiniMap.h"
#include "../CORE/TEXTURE/Texture.h"
#include "../CORE/LEVEL/Level.h"
#include "../IGRA/Player.h"
#include "../CORE/INPUT/Input.h"
#include "../src/Igra.h"
#include <iostream>


bool toggle = 0;

void MiniMap::Init(){
    _texture = new TextureComponent("../Assets/miniMap.jpg", Window::GetInstance().GetSize().m_X / 2 - 600 / 2, Window::GetInstance().GetSize().m_Y / 2 - 600 / 2, 600, 600, &Window::GetInstance().GetRenderer(), 1.0f, SDL_FLIP_NONE);
}


void MiniMap::Draw(Lab& l, Enemy& e){
    if ("menu" != Level::GetInstance().GetCurrentLevelName() && "options" != Level::GetInstance().GetCurrentLevelName() && toggle) {
        _texture->DrawS();
        
        if (Player::GetInstance().GetOrigin().GetDistance(l.GetIndexLab()._texture->_position) < WorldSettings::viewDistance) {
            LegacyTexture::GetInstance().CreateTexture(l.GetIndexLab()._texture->_filePath);
            LegacyTexture::GetInstance().DrawS(l.GetIndexLab()._texture->_filePath, _texture->_position.m_X + l.GetIndexLab()._texture->_position.m_X / m_MapScale, _texture->_position.m_Y + l.GetIndexLab()._texture->_position.m_Y / m_MapScale, l.GetIndexLab()._texture->_size.m_X, l.GetIndexLab()._texture->_size.m_Y, &Window::GetInstance().GetRenderer(), 0.05, SDL_FLIP_NONE);
        }
             
        for (std::vector<E>::iterator it = e.GetVect().begin(); it != e.GetVect().end(); it++) {
            if (Player::GetInstance().GetOrigin().GetDistance(it->_animation->_texture->_position) < WorldSettings::viewDistance) {
                LegacyTexture::GetInstance().CreateTexture("../Assets/nasprotnik.png");
                LegacyTexture::GetInstance().DrawS("../Assets/nasprotnik.png", _texture->_position.m_X + it->_animation->_texture->_position.m_X / m_MapScale, _texture->_position.m_Y + it->_animation->_texture->_position.m_Y / m_MapScale, 1920, 1920, &Window::GetInstance().GetRenderer(), 0.005, SDL_FLIP_NONE);
            }
        }
        LegacyTexture::GetInstance().CreateTexture("../Assets/player.png");
        LegacyTexture::GetInstance().DrawS("../Assets/player.png", _texture->_position.m_X + Player::GetInstance().GetOrigin().m_X / m_MapScale, _texture->_position.m_Y + Player::GetInstance().GetOrigin().m_Y / m_MapScale, 1920, 1920, &Window::GetInstance().GetRenderer(), 0.005, SDL_FLIP_NONE);
    }
}

void MiniMap::Update(){
    if (Input::GetInstance().GetKeyPressed(SDL_SCANCODE_M)) {
        toggle = !toggle;
    }
}