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