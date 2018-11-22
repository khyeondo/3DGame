#include "Cube.h"
#include "InputHandler.h"
#include "Camera.h"


Cube::Cube(SDL_Surface * surface, SDL_Surface * normalMap, Mesh * mesh) :
	GameObject3D(surface, normalMap, mesh)
{
}

void Cube::Init(GameState* pGameState)
{
	m_pos.x = -14.f;
}

void Cube::Update(GameState* pGameState)
{
	//m_angle.x += 0.1f;
	//m_angle.y += 0.1f;
	//m_angle.z += 0.1f;
	LookAt(Renderer3D::Instance()->GetCamera()->pos);
}

void Cube::Render()
{
	GameObject3D::Render();
}