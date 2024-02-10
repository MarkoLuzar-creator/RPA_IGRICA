#pragma once
#include <SDL.h>
#include <map>
#include "Vector2D.h"
#include <SDL_ttf.h>

class TextureComponent{
public:
	TextureComponent(const char* filePath, int x, int y, int w, int h, SDL_Renderer* renderer, float scale, SDL_RendererFlip f);
	TextureComponent(const TextureComponent& c);
	void DrawS();
	void DrawD();
	float _scale;
	Vector2D _position, _size;
	SDL_RendererFlip _flip;
	SDL_Rect _hitbox;
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	const char* _filePath;
};

class LegacyTexture {
public:
	static LegacyTexture& GetInstance() {
		static LegacyTexture instance;
		return instance;
	}
	void CreateTexture(const char* filePath);
	void DrawS(const char* filePath, int x, int y, int width, int height, SDL_Renderer* renderer, float scale, SDL_RendererFlip f);
private:
	std::map<const char*, SDL_Texture*> m_TextureMap;
};

class TTFText {
public:
	static TTFText& GetInstance() {
		static TTFText instance;
		return instance;
	}
	void RenderText(const char* msg, int x, int y, const char* font, int size = 20, int r = 255, int g = 255, int b = 255);
};

