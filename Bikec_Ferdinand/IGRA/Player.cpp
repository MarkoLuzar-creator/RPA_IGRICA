#include "Player.h"
#include "../CORE/TIMER/Timer.h"
#include "../CORE/INPUT/Input.h"
#include "../CORE/VECTOR/Vector.h"
#include "../CORE/PHYSICS/RigidBody.h"
#include "../src/Igra.h"
#include "../CORE/LEVEL/Level.h"
#include <iostream>



void Player::Init(const char* level, int x, int y, int w, int h, float s, SDL_Renderer* r, SDL_RendererFlip f) {
    _base = new AnimationComponent("../Assets/player_jump.png", x, y, w, h, 0, 8, 50, s, r, f);
    _movingL = new AnimationComponent("../Assets/player_roll.png", x, y, w, h, 0, 8, 50, s, r, f);
    _movingR = new AnimationComponent("../Assets/player_roll.png", x, y, w, h, 0, 8, 50, s, r, SDL_FLIP_VERTICAL);
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(0);
    _position = new Vector2D(x + w / 2, y + h / 2);
    _level = level;
}


Vector2D Player::GetOrigin(){
    return *_position;
}

SDL_Rect& Player::GetHitBox(){
    return _base->_texture->_hitbox;
}

void Player::Draw(){
    if (_level == Level::GetInstance().GetCurrentLevelName()) {
        if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_A)) {
            _movingL->DrawD();
        }
        else if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_D)) {
            _movingR->DrawD();
        }
        else if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_W)) {

        }
        else if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_S)) {

        }
        else {
            _base->DrawD();
        }
    }
}

void Player::Update() {
    if (_level == Level::GetInstance().GetCurrentLevelName()) {
        _base->_texture->_position = *_position;
        _movingL->_texture->_position = *_position;
        _movingR->_texture->_position = *_position;

        _base->Update();
        _movingL->Update();
        _movingR->Update();

        if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_A)) {
            m_RigidBody->ApplyForceX(-40);
        }
        if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_D)) {
            m_RigidBody->ApplyForceX(40);
        }
        if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_W)) {
            m_RigidBody->ApplyForceY(-40);
        }
        if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_S)) {
            m_RigidBody->ApplyForceY(40);
        }
        m_RigidBody->Update(Timer::GetInstance().GetDeltaTime());
        _position->TranslateX(m_RigidBody->GetPosition().m_X);
        _position->TranslateY(m_RigidBody->GetPosition().m_Y);

        m_RigidBody->ResetForce();

        if (_position->m_X > WorldSettings::worldSize) {
            _position->m_X = -WorldSettings::worldSize;
        }
        else if (_position->m_X < -WorldSettings::worldSize) {
            _position->m_X = WorldSettings::worldSize;
        }
        else if (_position->m_Y > WorldSettings::worldSize) {
            _position->m_Y = -WorldSettings::worldSize;
        }
        else if (_position->m_Y < -WorldSettings::worldSize) {
            _position->m_Y = WorldSettings::worldSize;
        }
    }
}