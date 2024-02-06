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
    void SetTargetReturn(Vector2D& go, Vector2D& ret);
    void Update();
    Vector2D& GetPosition();
private:
    Camera(){}
    Vector2D* _target, *_return, *_go, _position;
    bool _arrive;
};

