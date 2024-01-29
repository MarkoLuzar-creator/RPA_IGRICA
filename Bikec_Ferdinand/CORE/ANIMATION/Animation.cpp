#include "Animation.h"
#include "../TEXTURE/Texture.h"
#include <iostream>

void Animation::Update(){
	m_SpriteFrame = (SDL_GetTicks() / m_AnimationSpeed) % m_FrameCount;
}

void Animation::SetProperties(std::string textureID, int spriteRow, int numberOfFrames, int animationSpeed, SDL_RendererFlip flip){
	m_TextureID = textureID;
	m_SpriteRow = spriteRow;
	m_AnimationSpeed = animationSpeed;
	m_Flip = flip;
	m_FrameCount = numberOfFrames;
}

void Animation::Draw(int x, int y, int spriteWidth, int spriteHeight, float scale){
	Texture::GetInstance().DrawFrameStatic(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, m_Flip, scale);
}