#pragma once
#include <vector>
#include "../CORE/TextureComponent.h"

struct Tile {
	TextureComponent* _texture;
};

class World{
public:
	World(const char* level);
	void Push(const char* file, int x, int y, int w, int h, float s, SDL_Renderer& r, SDL_RendererFlip f);
	void Draw();
	void Update();
	const char* GetLevel();
	void Clear();
private:
	const char* _level;
	std::vector<Tile> _vect;
};

