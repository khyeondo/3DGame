#include "Bullet.h"
#include "InputHandler.h"
#include "Renderer3D.h"
#include "Camera.h"
#include "GameState.h"
#include "SurfaceManager.h"

Bullet::Bullet(SDL_Surface * surface, SDL_Surface * normalMap, Mesh * mesh) : 
	GameObject3D(surface, normalMap,mesh),m_force(this),m_light(this),m_colider(this)
{
	m_tag = "bullet";
	
	m_light.color = { 255,150,150 };
	m_light.brightness = 0.5f;

	m_colider.SetCollsionRange(1.f, 1.f);
}

void Bullet::Init(GameState* pGameState)
{
	m_pGameState = pGameState;
	m_firePos = m_pos;
}

void Bullet::Update()
{
	m_force.Update();
	LookAt(Renderer3D::Instance()->GetCamera()->pos);
	if ((m_firePos - m_pos).Length() > 200.f)
		m_pGameState->Destroy3DGameObject(this);
}

void Bullet::Collision(GameObject3D * other)
{
	if (other->GetTag() == "cube" || other->GetTag() == "monster")
	{
		m_pGameState->Destroy3DGameObject(this);
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
