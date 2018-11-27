#pragma once
#include "GameObject3D.h"
#include "Vec3.h"
#include "Light.h"

class Fire : public GameObject3D
{
private:
	Light m_light;

public:
	Fire(SDL_Surface* surface, SDL_Surface* normalMap, Mesh* mesh);
	~Fire() {
		GameObject3D::~GameObject3D();
	}
	virtual void Init(GameState* pGameState);
	virtual void Update();
	virtual void Render();

};