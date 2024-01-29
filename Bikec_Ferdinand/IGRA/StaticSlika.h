#pragma once
#include <SDL.h>
#include <string>
#include "../CORE/PHYSICS/Vector2D.h"
#include "../CORE/PHYSICS/RigidBody.h"
#include "../CORE/ANIMATION/Animation.h"


class StaticSlika{
public:
	StaticSlika(std::string baseTextureID, float x, float y, int width, int height, SDL_RendererFlip flip, std::string levelName);
	virtual void Draw();
	virtual void Update();
	virtual std::string& GetTextureID();
	virtual void SetTextureID(std::string);
private:
	std::string m_BaseTextureID, m_LevelID;
	Vector2D* m_Position;
	Vector2D* m_Size;
	SDL_RendererFlip m_Flip;
};

