#pragma once
#include <vector>
#include <engine.h>

struct Tile {
	TextureComponent* _texture;
};

class World{
public:
	World(const char* level);
	void Push(const char* file, int x, int y, int w, int h, float s, SDL_Renderer& r, SDL_RendererFlip f);
	void Draw();
	void Update();
	std::vector<Tile>& GetVect();
private:
	const char* _level;
	bool init = true;
	std::vector<Tile> _vect;
};

