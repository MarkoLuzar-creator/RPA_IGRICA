#pragma once
#include "TextureComponent.h"

class AnimationComponent{
public:
    AnimationComponent(const char* filePath, int x, int y, int w, int h, int row, int frames, int speed, float scale, SDL_Renderer* r, SDL_RendererFlip flip);
    void Update();
    void DrawD();
    void DrawS();
    TextureComponent* _texture;
    int _row, _frames, _speed, _spriteFrame;
};

