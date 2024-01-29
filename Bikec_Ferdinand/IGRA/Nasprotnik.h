#pragma once
#include "../CORE/PHYSICS/RigidBody.h"
#include "../CORE/ANIMATION/Animation.h"

class Nasprotnik{
public:
	Nasprotnik(std::string animationTexture, float x, float y, int width, int height, SDL_RendererFlip flip, std::string levelName);
	virtual void Draw();
	virtual void Update();
	virtual Vector2D& GetPosition();
	virtual Vector2D& GetSize();
private:
	SDL_Rect m_Hitbox{ 0, 0,0 ,0 };
	std::string m_BaseTextureID, m_LevelID;
	Vector2D* m_Position;
	Vector2D* m_Size;
	SDL_RendererFlip m_Flip;

	Vector2D* m_Origin;
	Animation* m_Animation;
	RigidBody* m_RigidBody;
};

