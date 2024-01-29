#pragma once
#include <cmath>

class Vector2D {
public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D operator+(const Vector2D& v2);
	Vector2D operator-(const Vector2D& v2);
	Vector2D operator*(const float scalar);
	void TranslateX(float velocityX);
	void TranslateY(float velocityY);
	void Translate(Vector2D velocityXY, float magnitude);
	float m_X, m_Y;
};