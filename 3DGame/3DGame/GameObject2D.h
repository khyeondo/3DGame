#pragma once
#include "GameObject.h"
#include "Vec2.h"

class GameObject2D : public GameObject
{
protected:
	Vec2 m_pos;
	
	string m_textureId;

public:
	GameObject2D();
	virtual ~GameObject2D();

	virtual void Init(GameState* pGameState);
	virtual void Update(GameState* pGameState);
	virtual void Render();

	Vec2 GetPos() {
		return m_pos;
	}
};