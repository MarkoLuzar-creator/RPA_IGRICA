#include "Camera.h"
#include "Window.h"
#include "Timer.h"
#include "Player.h"

void Camera::SetTarget(Vector2D& target){
	_target = &target;
}

void Camera::SetTargetReturn(Vector2D& go, Vector2D& ret){
	_go = &go;
	_return = &ret;
	_arrive = false;
}

void Camera::Update(){
	if (_return == nullptr) {
		_position = *_target;
	}
	else {
		if (!_arrive) {
			Vector2D dir = _position.GetDirectionVector(*_go);
			if (_position.GetDistance(*_go) > 50) {
				_position.Translate(dir, 5);
			}
			else {
				_arrive = true;
			}
		}
		else {
			Vector2D dir = _position.GetDirectionVector(*_return);
			if (_position.GetDistance(*_return) > 50) {
				_position.Translate(dir, 5);
				_return = nullptr;
			}
		}
	}
}

Vector2D& Camera::GetPosition(){
	return _position;
}

