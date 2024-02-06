#pragma once

const int FPS_LIMIT = 144;
const float TARGET_DELTATIME = 1.5f;

class Timer{
public:
	static Timer& GetInstance() {
		static Timer instance;
		return instance;
	}
	void Tick();
	float GetDeltaTime();
private:
	Timer(){}
	float m_DeltaTime = 0, m_LastTime = 0;
};

