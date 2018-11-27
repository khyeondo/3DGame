#pragma once

#include "GameObject2D.h" 
#include "Light.h"

class PlayerUI : public GameObject2D
{
private:
	GameObject * m_pPlayer;

	bool m_bShooting = false;
	Uint32 m_shootTicks;

public:
	PlayerUI(Vec2 pos, Vec2 size, std::string textureID) :
		GameObject2D(pos, size, textureID) {}
	~PlayerUI(){
		GameObject2D::~GameObject2D();
	}

	virtual void Init(GameState* pGameState);
	virtual void Update();
	virtual void Render();
};