#include "Timer.h"
#include <SDL.h>

void Timer::Tick(){
	m_DeltaTime = (SDL_GetTicks() - m_LastTime) * (FPS_LIMIT / 1000.0f);
	if (m_DeltaTime > TARGET_DELTATIME) {
		m_DeltaTime = TARGET_DELTATIME;
	}
	m_LastTime = SDL_GetTicks();
}

float Timer::GetDeltaTime(){
	return m_DeltaTime;
}
