#include "Nasprotnik.h"
#include "../CORE/TEXTURE/Texture.h"
#include "../CORE/LEVEL/Level.h"
#include "../CORE/VECTOR/Vector.h"
#include "../CORE/TIMER/Timer.h"
#include "../CORE/CAMERA/Camera.h"
#include "../IGRA/Igralec.h"

Nasprotnik::Nasprotnik(std::string animationTexture, float x, float y, int width, int height, SDL_RendererFlip flip, std::string levelName){
    m_Origin = new Vector2D(x + width / 2, y + height / 2);
    m_Animation = new Animation();
    m_RigidBody = new RigidBody();
    m_Position = new Vector2D(x, y);
    m_Size = new Vector2D(width, height);
    m_BaseTextureID = animationTexture;
    m_LevelID = levelName;
    m_Flip = flip;
	Vector::GetInstance().m_SeznamNasprotnikov.push_back(this);
}

void Nasprotnik::Draw(){
    if (m_LevelID == Level::GetInstance().GetCurrentLevelName())
	m_Animation->Draw(m_Position->m_X, m_Position->m_Y, m_Size->m_X, m_Size->m_Y, 0.5);
}

void Nasprotnik::Update(){
    if (m_LevelID == Level::GetInstance().GetCurrentLevelName()) {
        Vector2D offset = Camera::GetInstance().GetPosition();
        Vector2D pos = Window::GetInstance().GetScalePosition(m_Position->m_X, m_Position->m_Y, m_Size->m_X, m_Size->m_Y, offset);
        Vector2D size = Window::GetInstance().GetScaleSize(m_Size->m_X, m_Size->m_Y);
        m_Hitbox = { (int)pos.m_X, (int)pos.m_Y, (int)size.m_X, (int)size.m_Y };

        m_Animation->SetProperties(m_BaseTextureID, 0, 8, 50, m_Flip);
        m_RigidBody->ResetForce();

        if (m_Position->GetDistance(Igralec::GetInstance().GetOrigin()) < 8000) {
            Vector2D v = m_Position->GetDirectionVector(Igralec::GetInstance().GetOrigin());
            m_Position->Translate(v, 5);
        }

        m_RigidBody->Update(Timer::GetInstance().GetDeltaTime());
        m_Position->TranslateX(m_RigidBody->GetPosition().m_X);
        m_Position->TranslateY(m_RigidBody->GetPosition().m_Y);
        m_Animation->Update();

        m_Origin->m_X = m_Position->m_X + m_Size->m_X / 2;
        m_Origin->m_Y = m_Position->m_Y + m_Size->m_Y / 2;

        if (SDL_HasIntersection(&m_Hitbox, &Igralec::GetInstance().GetHitBox())) {
            exit(0);
        }
    }
}

Vector2D& Nasprotnik::GetPosition(){
    return *m_Position;
}

Vector2D& Nasprotnik::GetSize(){
    return *m_Size;
}
