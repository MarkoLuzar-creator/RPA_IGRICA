#include "MiniMap.h"
#include "../CORE/TEXTURE/Texture.h"
#include "../CORE/LEVEL/Level.h"
#include "StaticSlika.h"
#include "../CORE/VECTOR/Vector.h"
#include "../IGRA/Igralec.h"
#include "../CORE/PHYSICS/Math.h"
#include "../CORE/INPUT/Input.h"
#include <iostream>

float MiniMap::worldSize = 10000;
float MiniMap::viewDistance = 8000;
bool toggle = 0;

void MiniMap::Draw(){
    if (Level::GetInstance().GetCurrentLevelName() != "menu" && Level::GetInstance().GetCurrentLevelName() != "options" && toggle) {
        Texture::GetInstance().DrawStatic(m_BaseTextureID, m_Position->m_X, m_Position->m_Y, 600, 600, m_Flip);

        for (Arena* i : Vector::GetInstance().m_SeznamAren) {
            if (i == Vector::GetInstance().m_SeznamAren[Arena::m_ArenaIndex] && Math::GetInstance().GetDistanceFromPoints(Igralec::GetInstance().GetOrigin(), i->GetPosition()) < viewDistance) {
                Texture::GetInstance().DrawStatic(i->GetTextureID(), m_Position->m_X + i->GetPosition().m_X / m_MapScale, m_Position->m_Y + i->GetPosition().m_Y / m_MapScale, i->GetSize().m_X, i->GetSize().m_Y, SDL_FLIP_NONE, 0.02);
                   break;
            }
        }
        for (Nasprotnik* i : Vector::GetInstance().m_SeznamNasprotnikov) {
            if (Math::GetInstance().GetDistanceFromPoints(Igralec::GetInstance().GetOrigin(), i->GetPosition()) < viewDistance)
            Texture::GetInstance().DrawStatic("nasprotnik", m_Position->m_X + i->GetPosition().m_X / m_MapScale, m_Position->m_Y + i->GetPosition().m_Y / m_MapScale, 1920, 1920, SDL_FLIP_NONE, 0.005);
        }
        Texture::GetInstance().DrawStatic("igralec", m_Position->m_X + Igralec::GetInstance().GetOrigin().m_X / m_MapScale, m_Position->m_Y + Igralec::GetInstance().GetOrigin().m_Y / m_MapScale, 1920, 1920, SDL_FLIP_NONE, 0.005);
    }
}

bool change = 1;
void MiniMap::Update(){
    if (Input::GetInstance().GetKeyPressed(SDL_SCANCODE_M)) {
        toggle = !toggle;
    }
}

void MiniMap::SetProperties(std::string mapTextureID, float x, float y, int width, int height, SDL_RendererFlip flip){
    m_BaseTextureID = mapTextureID;
    m_Position = new Vector2D(x, y);
    m_Size = new Vector2D(width, height);
    m_Flip = flip;
}
