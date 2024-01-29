#include "Igralec.h"
#include "../CORE/TIMER/Timer.h"
#include "../CORE/INPUT/Input.h"
#include "../CORE/TEXTURE/Texture.h"
#include "../CORE/CAMERA/Camera.h"
#include "../IGRA/MiniMap.h"
#include "../CORE/PHYSICS/Math.h"
#include "../CORE/VECTOR/Vector.h"
#include "../CORE/PHYSICS/RigidBody.h"
#include "../CORE/ANIMATION/Animation.h"
#include <iostream>

void Igralec::SetProperties(std::string idleAnimationID, float x, float y, int width, int height, SDL_RendererFlip flip) {
    
    m_Position = new Vector2D(x, y);
    m_Size = new Vector2D(width, height);
    m_Flip = flip;

    m_BaseTextureID = idleAnimationID;
    m_Position = new Vector2D(x, y);
    m_Size = new Vector2D(width, height);
    m_Flip = flip;
    m_Origin = new Vector2D(x + width / 2, y + height / 2);
    m_Animation = new Animation();
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(0);
}

Vector2D& Igralec::GetOrigin(){
    return *m_Origin;
}

Vector2D& Igralec::GetSize(){
    return *m_Size;
}

std::string& Igralec::GetTextureID(){
    return m_BaseTextureID;
}

SDL_Rect& Igralec::GetHitBox(){
    return m_Hitbox;
}


void Igralec::Draw(){
    m_Animation->Draw(m_Position->m_X, m_Position->m_Y, m_Size->m_X, m_Size->m_Y, 0.5);
}

void Igralec::Update() {

    Vector2D offset = Camera::GetInstance().GetPosition();
    Vector2D pos = Window::GetInstance().GetScalePosition(m_Position->m_X, m_Position->m_Y, m_Size->m_X, m_Size->m_Y, offset);
    Vector2D size = Window::GetInstance().GetScaleSize(m_Size->m_X, m_Size->m_Y);
    m_Hitbox = { (int)pos.m_X, (int)pos.m_Y, (int)size.m_X, (int)size.m_Y };

    m_Animation->SetProperties(m_BaseTextureID, 0, 8, 50, m_Flip);
    m_RigidBody->ResetForce();

    if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_A)) {
        m_Animation->SetProperties("player_running", 0, 8, 50, SDL_FLIP_NONE);
        m_RigidBody->ApplyForceX(-40);
    }
    if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_D)) {
        m_Animation->SetProperties("player_running", 0, 8, 50, SDL_FLIP_HORIZONTAL);
        m_RigidBody->ApplyForceX(40);
    }
    if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_W)) {
        m_Animation->SetProperties("player_running", 0, 8, 50, SDL_FLIP_VERTICAL);
        m_RigidBody->ApplyForceY(-40);
    }
    if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_S)) {
        m_Animation->SetProperties("player_running", 0, 8, 50, SDL_FLIP_VERTICAL);
        m_RigidBody->ApplyForceY(40);
    }

    m_RigidBody->Update(Timer::GetInstance().GetDeltaTime());
    m_Position->TranslateX(m_RigidBody->GetPosition().m_X);
    m_Position->TranslateY(m_RigidBody->GetPosition().m_Y);
    m_Animation->Update();

    m_Origin->m_X = m_Position->m_X;
    m_Origin->m_Y = m_Position->m_Y;

    if (m_Origin->m_X > MiniMap::worldSize) {
        m_Position->m_X = -MiniMap::worldSize + 500 - m_Size->m_X / 2;
        m_Origin->m_X = m_Position->m_X + m_Size->m_X / 2;
    }
    else if (m_Origin->m_X < -MiniMap::worldSize) {
        m_Position->m_X = MiniMap::worldSize - 500 - m_Size->m_X / 2;
        m_Origin->m_X = m_Position->m_X + m_Size->m_X / 2;
    }else if (m_Origin->m_Y > MiniMap::worldSize) {
        m_Position->m_Y = -MiniMap::worldSize + 500 - m_Size->m_Y / 2;
        m_Origin->m_Y = m_Position->m_Y + m_Size->m_Y / 2;
    }
    else if (m_Origin->m_Y < -MiniMap::worldSize) {
        m_Position->m_Y = MiniMap::worldSize - 500 - m_Size->m_Y / 2;
        m_Origin->m_Y = m_Position->m_Y + m_Size->m_Y / 2;
    }
}