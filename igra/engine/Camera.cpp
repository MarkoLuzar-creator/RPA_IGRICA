#include "Camera.h"
#include "Window.h"

void Camera::SetOriginPosition(int x, int y){
	m_ViewBox = { 0, 0, (int)Window::GetInstance().GetSize().m_X, (int)Window::GetInstance().GetSize().m_X };
	m_Origin = Vector2D(x, y);
}

void Camera::Update(Vector2D target){
	m_ViewBox.x = target.m_X - m_Origin.m_X / 2;
	m_ViewBox.y = target.m_Y - m_Origin.m_Y / 2;
	m_Position = Vector2D(m_ViewBox.x, m_ViewBox.y);
}

Vector2D& Camera::GetPosition(){
	return m_Position;
}
