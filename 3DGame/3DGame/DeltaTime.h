#pragma once

#include <SDL.h>

class DeltaTime
{
public:
	static DeltaTime * Instance() {
		if (m_pInst == 0)
			m_pInst = new DeltaTime();
		return m_pInst;
	}

private:
	static DeltaTime * m_pInst;
	DeltaTime() {
		now = SDL_GetPerformanceCounter();
		last = 0;
		deltaTime = 0;
	}

private:
	Uint64 now;
	Uint64 last;

	double deltaTime;
	float gameSpeed = 1.f;

public:
	void SetDeltaTime() {
		last = now;
		now = SDL_GetPerformanceCounter();

		deltaTime = (double)((now - last) / (double)SDL_GetPerformanceFrequency());
	}
	void SetGameSpeed(float speed) {
		gameSpeed = speed;
	}

	double GetDeltaTime() {
		return deltaTime * gameSpeed;
	}

};

#define DELTATIME (float)(DeltaTime::Instance()->GetDeltaTime())