#pragma once
#include <vector>
#include <engine.h>

struct E {
	AnimationComponent* _animation;
	RigidBody* _rigidBody;
};

class Enemy{
public:
	Enemy(const char* level);
	void Push(const char* file, int x, int y, int w, int h, int row, int frames, int speed, float s, SDL_Renderer* r, SDL_RendererFlip f);
	void Draw();
	void Update();
	std::vector<E>& GetVect();
private:
	const char* _level;
	std::vector<E> _vect;
};

