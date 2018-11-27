#pragma once

#include "GameObject2D.h"

class Pause : public GameObject2D
{
public:
	Pause(Vec2 pos, Vec2 size, std::string textureID) :
		GameObject2D(pos, size, textureID) {}
	~Pause() {
		GameObject2D::~GameObject2D();
	}

	bool m_bPause = false;

private:
	virtual void Init(GameState* pGameState);
	virtual void Update();
	virtual void Render();
};