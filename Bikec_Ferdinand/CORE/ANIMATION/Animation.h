#pragma once
#include "../WINDOW/Window.h"

class Animation{
public:
	void Update();
	void SetProperties(std::string textureID, int spriteRow, int numberOfFrames, int animationSpeed, SDL_RendererFlip flip);
	void Draw(int x, int y, int spriteWidth, int spriteHeight, float scale = 1);
private:
	int m_SpriteRow, m_SpriteFrame;
	int m_AnimationSpeed, m_FrameCount;
	std::string m_TextureID;
	SDL_RendererFlip m_Flip;
};

