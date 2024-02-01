#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include "../CORE/TextureComponent.h"
#include "../IGRA/MiniMap.h"

class Arena{
public:
	Arena(const char* texture, const char* level, int x, int y, int w, int h, float s, SDL_Renderer* r, SDL_RendererFlip f);
	virtual void Draw();
	virtual void Update();
	static int m_ArenaIndex;
	static std::vector<Arena> _arene;
	static int _steviloAren;
	friend class MiniMap;
private:
	int _pushanIndex;
	const char* _level;
	TextureComponent* _texture;
};

