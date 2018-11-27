#pragma once

#include "GameObject3D.h"
#include "Vec3.h"
#include "Collider.h"

class Cube : public GameObject3D
{
private:
	Collider m_collider;
public:
	Cube(SDL_Surface * surface, SDL_Surface * normalMap, Mesh * mesh);
	~Cube() {
		GameObject3D::~GameObject3D();
	}
	virtual void Init(GameState* pGameState);
	virtual void Update();
	virtual void Collision(GameObject3D* other);
	virtual void Render();
};