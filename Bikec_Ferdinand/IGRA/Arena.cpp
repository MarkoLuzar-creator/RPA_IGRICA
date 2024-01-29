#include "Arena.h"
#include "../CORE/VECTOR/Vector.h"
#include "../CORE/TEXTURE/Texture.h"
#include "../CORE/LEVEL/Level.h"

#include "../CORE/CAMERA/Camera.h"
#include "../IGRA/Igralec.h"
#include "../CORE/INPUT/Input.h"

int Arena::m_ArenaIndex = 0;

Arena::Arena(std::string baseTextureID, float x, float y, int width, int height, SDL_RendererFlip flip, std::string levelName){
	m_Position = new Vector2D(x, y);
	m_Size = new Vector2D(width, height);
	m_BaseTextureID = baseTextureID;
	m_LevelID = levelName;
	m_Flip = flip;

	Vector2D offset = Camera::GetInstance().GetPosition();
	Vector2D pos = Window::GetInstance().GetScalePosition(m_Position->m_X, m_Position->m_Y, m_Size->m_X, m_Size->m_Y, offset);
	Vector2D size = Window::GetInstance().GetScaleSize(m_Size->m_X, m_Size->m_Y);
	m_Hitbox = { (int)pos.m_X, (int)pos.m_Y, (int)size.m_X, (int)size.m_Y };

	bool overlap = false;
	for (Arena* i : Vector::GetInstance().m_SeznamAren) {
		if (SDL_HasIntersection(&i->GetHitbox(), &m_Hitbox)) {
			overlap = true;
			break;
		}
	}

	if (!overlap)
	Vector::GetInstance().m_SeznamAren.push_back(this);
}

void Arena::Draw() {
	if (m_LevelID == Level::GetInstance().GetCurrentLevelName()) {
		if (this == Vector::GetInstance().m_SeznamAren[m_ArenaIndex]) {
			Texture::GetInstance().DrawDynamic(m_BaseTextureID, m_Position->m_X, m_Position->m_Y, m_Size->m_X, m_Size->m_Y, m_Flip);
		}
	}
}


void Arena::Update(){
	Vector2D offset = Camera::GetInstance().GetPosition();
	Vector2D pos = Window::GetInstance().GetScalePosition(m_Position->m_X, m_Position->m_Y, m_Size->m_X / 3, m_Size->m_Y / 3, offset);
	Vector2D size = Window::GetInstance().GetScaleSize(m_Size->m_X / 3, m_Size->m_Y / 3);
	m_Hitbox = { (int)pos.m_X, (int)pos.m_Y, (int)size.m_X, (int)size.m_Y};

	if (SDL_HasIntersection(&Igralec::GetInstance().GetHitBox(), &m_Hitbox) && this == Vector::GetInstance().m_SeznamAren[m_ArenaIndex] && m_ArenaIndex < Vector::GetInstance().m_SeznamAren.size() - 1) {
		if (this == Vector::GetInstance().m_SeznamAren[m_ArenaIndex]) {
			m_ArenaIndex++;
		}
	}

}

Vector2D& Arena::GetPosition(){
	return *m_Position;
}

Vector2D& Arena::GetSize(){
	return *m_Size;
}

std::string& Arena::GetTextureID(){
	return m_BaseTextureID;
}

SDL_Rect& Arena::GetHitbox(){
	return m_Hitbox;
}
