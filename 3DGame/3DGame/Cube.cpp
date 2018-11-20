#include "Cube.h"
#include "InputHandler.h"
#include "Camera.h"


Cube::Cube(SDL_Surface * surface, SDL_Surface * normalMap, Mesh * mesh) :
	GameObject3D(surface, normalMap, mesh)
{
	Init();
}

void Cube::Init()
{
	m_pos.x = -14.f;
}

void Cube::Update()
{
	//m_angle.x += 0.1f;
	//m_angle.y += 0.1f;
	//m_angle.z += 0.1f;
	//Vec3 a = m_pos - Renderer3D::Instance()->GetCamera()->pos;
	//m_angle.y = atan2(a.z , a.x);
}

void Cube::Render()
{
	GameObject3D::Render();
}