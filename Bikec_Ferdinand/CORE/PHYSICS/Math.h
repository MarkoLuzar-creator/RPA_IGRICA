#pragma once
#include "Vector2D.h"

class Math{
public:
	static Math& GetInstance() {
		static Math instance;
		return instance;
	}
	float GetDistanceFromPoints(Vector2D T1, Vector2D T2) {
		float d = sqrt(pow(T2.m_X - T1.m_X, 2) + pow(T2.m_Y - T1.m_Y, 2));
		return d;
	}

	Vector2D& GetDirectionVector(Vector2D from, Vector2D to) {
		float dx = to.m_X - from.m_X;
		float dy = to.m_Y - from.m_Y;

		float distance = sqrt(dx * dx + dy * dy);


		if (distance == 0.0f) {
			Vector2D v;
			return v;
		}

		float invDistance = 1.0f / distance;
		Vector2D v(dx * invDistance, dy * invDistance);
		return v;
	}
};

