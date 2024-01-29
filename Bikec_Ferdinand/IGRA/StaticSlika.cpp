#include "StaticSlika.h"
#include "../CORE/VECTOR/Vector.h"
#include "../CORE/TEXTURE/Texture.h"
#include "../CORE/LEVEL/Level.h"

StaticSlika::StaticSlika(std::string baseTextureID, float x, float y, int width, int height, SDL_RendererFlip flip, std::string levelName){
	m_Position = new Vector2D(x, y);
	m_Size = new Vector2D(width, height);
	m_BaseTextureID = baseTextureID;
	m_LevelID = levelName;
	m_Flip = flip;
	Vector::GetInstance().m_SeznamStatičnihSlik.push_back(this);
}

void StaticSlika::Draw(){
	if (m_LevelID == Level::GetInstance().GetCurrentLevelName())
	Texture::GetInstance().DrawDynamic(m_BaseTextureID, m_Position->m_X, m_Position->m_Y, m_Size->m_X, m_Size->m_Y, m_Flip);
}

void StaticSlika::Update(){
}

std::string& StaticSlika::GetTextureID(){
	return m_BaseTextureID;
}

void StaticSlika::SetTextureID(std::string a){
	m_BaseTextureID = a;
}
