#include "Vector2D.h"

Vector2D::Vector2D() {
	m_X = 0;
	m_Y = 0;
}

Vector2D::Vector2D(float x, float y) {
	m_X = x;
	m_Y = y;
}

Vector2D Vector2D::operator+(const Vector2D& v2) {
	return Vector2D(m_X + v2.m_X, m_Y + v2.m_Y);
}

Vector2D Vector2D::operator-(const Vector2D& v2) {
	return Vector2D(m_X - v2.m_X, m_Y - v2.m_Y);
}

Vector2D Vector2D::operator*(const float scalar) {
	return Vector2D(m_X * scalar, m_Y * scalar);
}

float Vector2D::GetDistance(const Vector2D& v2){
	float d = sqrt(pow(m_X - v2.m_X, 2) + pow(m_Y - v2.m_Y, 2));
	d = abs(d);
	return d;
}

Vector2D Vector2D::GetDirectionVector(const Vector2D& v2){
	float dx = v2.m_X - m_X;
	float dy = v2.m_Y - m_Y;
	float distance = sqrt(dx * dx + dy * dy);

	if (distance == 0.0f) {
		Vector2D v;
		return v;
	}

	float invDistance = 1.0f / distance;
	Vector2D v(dx * invDistance, dy * invDistance);
	return v;
}


void Vector2D::TranslateX(float velocityX){
	m_X += velocityX;
}

void Vector2D::TranslateY(float velocityY){
	m_Y += velocityY;
}

void Vector2D::Translate(Vector2D velocityXY, float magnitude){
	m_X += velocityXY.m_X * magnitude;
	m_Y += velocityXY.m_Y * magnitude;
}