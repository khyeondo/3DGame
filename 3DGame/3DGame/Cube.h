#pragma once

#include "GameObject3D.h"
#include "Vec3.h"

class Cube : public GameObject3D
{
private:

public:
	Cube(SDL_Surface * surface, SDL_Surface * normalMap, Mesh * mesh);

	virtual void Init();
	virtual void Update();
	virtual void Render();
};