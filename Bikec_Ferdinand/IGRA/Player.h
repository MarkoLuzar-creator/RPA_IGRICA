#pragma once
#include <SDL.h>
#include <string>
#include "../CORE/PHYSICS/Vector2D.h"
#include "../CORE/PHYSICS/RigidBody.h"
#include "../CORE/AnimationComponent.h"

class Player{
public:
	static Player& GetInstance() {
		static Player instance;
		return instance;
	}
	void Draw();
	void Update();
	void Init(const char* level, int x, int y, int w, int h, float s, SDL_Renderer* r, SDL_RendererFlip f);
	Vector2D GetOrigin();
	SDL_Rect& GetHitBox();
private:
	const char* _level;
	AnimationComponent* _base;
	AnimationComponent* _movingL;
	AnimationComponent* _movingR;
	AnimationComponent* _movingU;
	AnimationComponent* _movingD;

	Vector2D* _position;
	RigidBody* m_RigidBody;
};
