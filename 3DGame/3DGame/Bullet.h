#pragma once

#include "GameObject3D.h"
#include "Vec3.h"
#include "Force.h"

class Bullet : public GameObject3D
{
private:
	Force m_force;

public:
	Bullet(SDL_Surface* surface, SDL_Surface* normalMap, Mesh* mesh);

	virtual void Init(GameState* pGameState);
	virtual void Update(GameState* pGameState);
	virtual void Render();

	void SetDir(Vec3 dir);
};