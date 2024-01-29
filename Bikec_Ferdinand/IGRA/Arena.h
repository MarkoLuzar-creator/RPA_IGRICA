#pragma once
#include <SDL.h>
#include <string>
#include "../CORE/PHYSICS/Vector2D.h"

class Arena{
public:
	Arena(std::string baseTextureID, float x, float y, int width, int height, SDL_RendererFlip flip, std::string levelName);
	virtual void Draw();
	virtual void Update();
	Vector2D& GetPosition();
	Vector2D& GetSize();
	std::string& GetTextureID();
	SDL_Rect& GetHitbox();
	static int m_ArenaIndex;
private:
	SDL_Rect m_Hitbox{ 0, 0, 0, 0 };
	std::string m_BaseTextureID, m_LevelID;
	Vector2D* m_Position;
	Vector2D* m_Size;
	SDL_RendererFlip m_Flip;
};
