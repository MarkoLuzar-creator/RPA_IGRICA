#pragma once
#include <SDL.h>
#include <iostream>
#include "Vector2D.h"

class Camera{
public:
    static Camera& GetInstance() {
        static Camera instance;
        return instance;
    }
    void SetOriginPosition(int x, int y);
    void Update(Vector2D target);
    Vector2D& GetPosition();
private:
    Camera(){}
    Vector2D m_Origin;
    SDL_Rect m_ViewBox;
    Vector2D m_Position;
};

