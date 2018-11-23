#include "Bullet.h"
#include "InputHandler.h"
#include "Renderer3D.h"
#include "Camera.h"
#include "GameState.h"
#include "SurfaceManager.h"

Bullet::Bullet(SDL_Surface * surface, SDL_Surface * normalMap, Mesh * mesh) : 
	GameObject3D(surface, normalMap,mesh),m_force(this),m_light(this),m_colider(this)
{
	m_tag = "Bullet";
	
	m_light.color = { 255,0,0 };
	m_light.brightness = 0.4f;

	m_colider.SetCollsionRage(5.f, 5.f);
}

void Bullet::Init(GameState* pGameState)
{
	m_pGameState = pGameState;
}

void Bullet::Update(GameState* pGameState)
{
	m_force.Update();
	LookAt(Renderer3D::Instance()->GetCamera()->pos);
}

void Bullet::Collision(GameObject3D * other)
{
	if (other->GetTag() == "cube")
	{
		m_pGameState->DestroyGameObject(this);
	}
}

void Bullet::Render()
{
	GameObject3D::Render();
}

void Bullet::SetDir(Vec3 dir)
{
	m_force.RefVelocity() = dir;
}
