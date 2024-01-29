#pragma once
#include "Vector2D.h"

class RigidBody {
public:
	RigidBody();
	void SetMass(float mass);
	void SetGravity(float gravity);
	float GetMass();
	Vector2D GetPosition();
	Vector2D GetVelocity();
	Vector2D GetAccelaration();
	void ApplyForce(Vector2D F);
	void ApplyForceX(float Fx);
	void ApplyForceY(float Fy);
	void ApplyFriction(Vector2D k);
	void ResetFriction();
	void ResetForce();
	void Update(float deltaTime);
private:
	float m_Mass, m_Gravity;
	Vector2D m_Force, m_Friction;
	Vector2D m_Position, m_Velocity, m_Accelaration;
};
