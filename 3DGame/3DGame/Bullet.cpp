#include "Bullet.h"
#include "InputHandler.h"
#include "Renderer3D.h"
#include "Camera.h"

#include "SurfaceManager.h"

Bullet::Bullet(SDL_Surface * surface, SDL_Surface * normalMap, Mesh * mesh) : 
	GameObject3D(surface, normalMap,mesh),m_force(this)
{
	m_tag = "Bullet";
}

void Bullet::Init(GameState* pGameState)
{
}

void Bullet::Update(GameState* pGameState)
{
	m_force.Update();
	LookAt(Renderer3D::Instance()->GetCamera()->pos);
}

void Bullet::Render()
{
	GameObject3D::Render();
}

void Bullet::SetDir(Vec3 dir)
{
	m_force.RefVelocity() = dir;
}
