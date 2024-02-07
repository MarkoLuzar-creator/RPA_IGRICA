#include "Camera.h"
#include "Window.h"
#include "Timer.h"
#include "Player.h"

void Camera::SetTarget(Vector2D& target){
	_target = &target;
}

void Camera::SetAnimationTarget(Vector2D& target){
	_animationTarget = &target;
}

void Camera::Update(){
	if (_animationTarget == nullptr) {
		_position = *_target;
	}
}

void Camera::UpdateAnimation(){
	if (_animationTarget != nullptr) {
		Vector2D dir = _position.GetDirectionVector(*_animationTarget);
		if (_position.GetDistance(*_animationTarget) > 500) {
			_position.Translate(dir, 15);
		}
		else if (_position.GetDistance(*_animationTarget) > 50) {
			_position.Translate(dir, 5);
		}
		else if (_position.GetDistance(*_animationTarget) > 5) {
			_animationTarget = nullptr;
		}
	}
}

Vector2D& Camera::GetPosition(){
	return _position;
}

