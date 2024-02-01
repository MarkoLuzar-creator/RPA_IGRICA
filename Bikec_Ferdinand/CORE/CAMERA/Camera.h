#pragma once
#include "../PHYSICS/Vector2D.h"
#include "../WINDOW/Window.h"
#include <SDL.h>
#include <iostream>



class Camera{
public:
    static Camera& GetInstance() {
        static Camera instance;
        return instance;
    }
    void SetOriginPosition(int x, int y) {
        m_Origin = Vector2D(x, y);
    }
    void Update(Vector2D target) {
        m_ViewBox.x = target.m_X - m_Origin.m_X / 2;
        m_ViewBox.y = target.m_Y - m_Origin.m_Y / 2;
        m_Position = Vector2D(m_ViewBox.x, m_ViewBox.y);
    }
    Vector2D& GetPosition(){
        return m_Position;
    }
private:
    Camera(){}
    Vector2D m_Origin;
    SDL_Rect m_ViewBox = { 0, 0, (int)Window::GetInstance().GetSize().m_X, (int)Window::GetInstance().GetSize().m_X };
    Vector2D m_Position;
};

