#pragma once

#include "GameObject3D.h"
#include "Vec3.h"

class Cube : public GameObject3D
{
private:

public:
	Cube(SDL_Surface * surface, SDL_Surface * normalMap, Mesh * mesh);

	virtual void Init(GameState* pGameState);
	virtual void Update(GameState* pGameState);
	virtual void Render();
};