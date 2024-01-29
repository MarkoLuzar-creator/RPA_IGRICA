#include "KlasičniGumb.h"
#include "../CORE/TEXTURE/Texture.h"
#include "../CORE/VECTOR/Vector.h"
#include "../CORE/LEVEL/Level.h"
#include "../CORE/INPUT/Input.h"
#include "../CORE/CAMERA/Camera.h"
#include "Igralec.h"
#include <iostream>

KlasičniGumb::KlasičniGumb(std::string baseTextureID, std::string hoverTextureID, float x, float y, int width, int height, SDL_RendererFlip flip, std::string levelName, ButtonTypes buttonType){
	trenutnaTextura = baseTextureID;
	tipGumba = buttonType;
	m_Position = new Vector2D(x, y);
	m_Size = new Vector2D(width, height);
	m_BaseTextureID = baseTextureID;
	m_LevelID = levelName;
	m_Flip = flip;
	m_HoverTextureID = hoverTextureID;
	//Vector::GetInstance().m_SeznamKlasičnihGumbov.push_back(this);
}

void KlasičniGumb::Draw(){
	if (m_LevelID == Level::GetInstance().GetCurrentLevelName())
	Texture::GetInstance().DrawStatic(trenutnaTextura, m_Position->m_X, m_Position->m_Y, m_Size->m_X, m_Size->m_Y, m_Flip);
}

void KlasičniGumb::Update(){
	if (m_LevelID == Level::GetInstance().GetCurrentLevelName()) {
		trenutnaTextura = m_BaseTextureID;
		Vector2D offset;
		offset = Camera::GetInstance().GetPosition();
		Vector2D pos = Window::GetInstance().GetScalePosition(m_Position->m_X, m_Position->m_Y, m_Size->m_X, m_Size->m_Y, offset);
		Vector2D size = Window::GetInstance().GetScaleSize(m_Size->m_X, m_Size->m_Y);

		SDL_Rect button = { pos.m_X, pos.m_Y, size.m_X, size.m_Y };
		SDL_Rect mouse = { Input::GetInstance().GetMousePosition().m_X, Input::GetInstance().GetMousePosition().m_Y, 1, 1};

		if (SDL_HasIntersection(&mouse, &button)) {
			trenutnaTextura = m_HoverTextureID;
			if (Input::GetInstance().GetMouseClick(SDL_BUTTON_LEFT)) {
				switch (tipGumba) {
				case ButtonTypes::Play: Level::GetInstance().NextLevel(); break;
				case ButtonTypes::Exit: exit(0); break;
				case ButtonTypes::Options: Level::GetInstance().SetLevel("options"); break;
				case ButtonTypes::Home: Level::GetInstance().SetLevel("menu"); break;
				}
				Input::GetInstance().UpdateMouseClicks();
			}
		}
	}
}
