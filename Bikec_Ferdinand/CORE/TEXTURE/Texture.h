#pragma once
#include "../WINDOW/Window.h"

class Texture{
public:
	static Texture& GetInstance() {
		static Texture instance;
		return instance;
	}
	void Load(std::string id, std::string fileName);
	void DrawDynamic(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip, float scale = 1);
	void DrawStatic(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip, float scale = 1);
	void DrawFrameDynamic(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip, float scale = 1);
	void DrawFrameStatic(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip, float scale = 1);
private:
	Texture(){}
	std::map<std::string, SDL_Texture*> m_TextureMap;
};

