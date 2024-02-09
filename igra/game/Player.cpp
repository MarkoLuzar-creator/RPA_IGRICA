#include "Player.h"
#include <iostream>
#include <Igra.h>



void Player::Init(int x, int y, int w, int h, float s, SDL_Renderer* r, SDL_RendererFlip f) {
    _base = new AnimationComponent("../assets/player_jump.png", x, y, w, h, 0, 8, 50, s, r, f);
    _movingL = new AnimationComponent("../assets/player_roll.png", x, y, w, h, 0, 8, 50, s, r, f);
    _movingR = new AnimationComponent("../assets/player_roll.png", x, y, w, h, 0, 8, 50, s, r, SDL_FLIP_VERTICAL);
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(0);
    _position = new Vector2D(x + w / 2, y + h / 2);
}


Vector2D& Player::GetOrigin(){
    return *_position;
}

SDL_Rect& Player::GetHitBox(){
    return _base->_texture->_hitbox;
}

void Player::Draw(){
    if (1) {
        if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_A)) {
            _movingL->DrawD();
        }
        else if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_D)) {
            _movingR->DrawD();
        }
        else if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_W)) {
            _movingR->DrawD();
        }
        else if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_S)) {
            _movingR->DrawD();
        }
        else {
            _base->DrawD();
        }
    }
}

void Player::Update() {
    if (1 && _canMove) {
        _base->_texture->_position = *_position;
        _movingL->_texture->_position = *_position;
        _movingR->_texture->_position = *_position;

        _base->Update();
        _movingL->Update();
        _movingR->Update();

        if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_A)) {
            m_RigidBody->ApplyForceX(-20);
        }
        if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_D)) {
            m_RigidBody->ApplyForceX(20);
        }
        if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_W)) {
            m_RigidBody->ApplyForceY(-20);
        }
        if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_S)) {
            m_RigidBody->ApplyForceY(20);
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