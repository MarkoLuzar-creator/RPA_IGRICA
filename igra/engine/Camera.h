#pragma once
#include <SDL.h>
#include <iostream>
#include "Vector2D.h"
#include "RigidBody.h"

class Camera{
public:
    static Camera& GetInstance() {
        static Camera instance;
        return instance;
    }
    void SetTarget(Vector2D& target);
    void SetAnimationTarget(Vector2D& target);
    void Update();
    void UpdateAnimation();
    Vector2D& GetPosition();
private:
    Camera(){}
    Vector2D* _target, _position;
    Vector2D* _animationTarget;
    bool _arrive;
};

