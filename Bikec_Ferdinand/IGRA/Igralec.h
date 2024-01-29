#pragma once
#include <SDL.h>
#include <string>
#include "../CORE/PHYSICS/Vector2D.h"
#include "../CORE/PHYSICS/RigidBody.h"
#include "../CORE/ANIMATION/Animation.h"

class Igralec{
public:
	static Igralec& GetInstance() {
		static Igralec instance;
		return instance;
	}
	virtual void Draw();
	virtual void Update();
	virtual void SetProperties(std::string idleAnimationID, float x, float y, int width, int height, SDL_RendererFlip flip);
	virtual Vector2D& GetOrigin();
	virtual Vector2D& GetSize();
	virtual std::string& GetTextureID();
	virtual SDL_Rect& GetHitBox();
private:
	Igralec(){}
	SDL_Rect m_Hitbox = { 0, 0, 0, 0 };
	std::string m_BaseTextureID;
	Vector2D* m_Position;
	Vector2D* m_Size;
	SDL_RendererFlip m_Flip;

	Vector2D* m_Origin;
	Animation* m_Animation;
	RigidBody* m_RigidBody;
};
