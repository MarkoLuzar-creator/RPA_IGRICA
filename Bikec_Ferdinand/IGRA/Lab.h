#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include "../CORE/TextureComponent.h"

struct L {
	TextureComponent* _texture;
	int _index;
};

class Lab {
public:
	Lab(const char* level);
	void Push(const char* file, int x, int y, int w, int h, float s, SDL_Renderer& r, SDL_RendererFlip f);
	void Draw();
	void Update();
	const char* GetLevel();
	L& GetIndexLab();
	void Clear();
private:
	int _index;
	const char* _level;
	std::vector<L> _vect;
};

