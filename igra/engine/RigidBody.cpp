#include "RigidBody.h"

RigidBody::RigidBody() {
	m_Mass = 1.0f;
	m_Gravity = 0.0f;
}

void RigidBody::SetMass(float mass) {
	m_Mass = mass;
}

void RigidBody::SetGravity(float gravity) {
	m_Gravity = gravity;
}

float RigidBody::GetMass() {
	return m_Mass;
}

Vector2D RigidBody::GetPosition() {
	return m_Position;
}

Vector2D RigidBody::GetVelocity() {
	return m_Velocity;
}

Vector2D RigidBody::GetAccelaration() {
	return m_Accelaration;
}

void RigidBody::ApplyForce(Vector2D F) {
	m_Force = F;
}

void RigidBody::ApplyForceX(float Fx) {
	m_Force.m_X = Fx;
}

void RigidBody::ApplyForceY(float Fy) {
	m_Force.m_Y = Fy;
}

void RigidBody::ApplyFriction(Vector2D k) {
	m_Friction = k;
}

void RigidBody::ResetFriction() {
	m_Friction = Vector2D(0, 0);
}

void RigidBody::ResetForce() {
	m_Force = Vector2D(0, 0);
}

void RigidBody::Update(float deltaTime) {
	m_Accelaration.m_X = (m_Force.m_X + m_Friction.m_X) / m_Mass;
	m_Accelaration.m_Y = m_Gravity + m_Force.m_Y / m_Mass;
	m_Velocity = m_Accelaration * deltaTime;
	m_Position = m_Velocity * deltaTime;
}
