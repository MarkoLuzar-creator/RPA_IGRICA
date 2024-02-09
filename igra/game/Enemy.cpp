#include "Enemy.h"
#include <Player.h>
#include <Igra.h>
#include <MiniMap.h>


Enemy::Enemy(const char* level){
    _level = level;
}

void Enemy::Push(const char* file, int x, int y, int w, int h, int row, int frames, int speed, float s, SDL_Renderer* r, SDL_RendererFlip f){
    E a;
    a._animation = new AnimationComponent(file, x, y, w, h, row, frames, speed, s, r, f);
    a._rigidBody = new RigidBody();
    a._rigidBody->SetGravity(0);
    _vect.push_back(a);
}

void Enemy::Draw(){
    int i = 0;
    for (std::vector<E>::iterator it = _vect.begin(); it != _vect.end(); it++) {
        if (_level == Level::GetInstance().GetCurrentLevelName()) {
            it->_animation->DrawD();
        }
        else {
            break;
        }
    }
}

void Enemy::Update() {
    if (_level == Level::GetInstance().GetCurrentLevelName() && Player::GetInstance()._canMove){
        for (std::vector<E>::iterator it = _vect.begin(); it != _vect.end(); it++) {
            if (init) {
                MiniMap::GetInstance().LoadEnemy(*this);
                init = false;
            }
            if (_level == Level::GetInstance().GetCurrentLevelName()) {
                it->_animation->Update();
                if (it->_animation->_texture->_position.GetDistance(Player::GetInstance().GetOrigin()) < 3000) {
                    Vector2D dir = it->_animation->_texture->_position.GetDirectionVector(Player::GetInstance().GetOrigin());
                    it->_animation->_texture->_position.Translate(dir, 8);
                }
                it->_rigidBody->Update(Timer::GetInstance().GetDeltaTime());
                it->_animation->_texture->_position.TranslateX(it->_rigidBody->GetPosition().m_X);
                it->_animation->_texture->_position.TranslateY(it->_rigidBody->GetPosition().m_Y);
                if (SDL_HasIntersection(&it->_animation->_texture->_hitbox, &Player::GetInstance().GetHitBox())) {
                    _vect.erase(it);
                    break;
                }
            }
            else {
                break;
            }

        }
    }
}

std::vector<E>& Enemy::GetVect(){
    return _vect;
}
