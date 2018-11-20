#pragma once

#include "GameObject3D.h"
#include "Vec3.h"

class Plane : public GameObject3D
{
private:

public:
	Plane(SDL_Surface * surface, SDL_Surface * normalMap, Mesh * mesh);

	virtual void Init();
	virtual void Update();
	virtual void Render();
};