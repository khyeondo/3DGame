#include "Monster.h"
#include "GameState.h"
#include "SurfaceManager.h"
#include "Player.h"

int Monster::s_monsterCount = 0;

Monster::Monster(SDL_Surface * surface, SDL_Surface * normalMap, Mesh * mesh) :
	GameObject3D(surface,normalMap,mesh),m_force(this),m_collider(this)
{
}

void Monster::Init(GameState * pGameState)
{
	s_monsterCount++;
	m_collider.SetCollisionRange(10.f, 100.f);
	m_pGameState = pGameState;
	m_pPlayer = pGameState->Find3DObjectWithTag("player");
	m_moveSpeed = 10.f;
	m_hp = 10;
	m_tag = "monster";
	m_scale = Vec3(30.f, 0.f, 40.f);
	m_angle = Vec3(M_PI / 2.f, M_PI, 0.f);
}

void Monster::Update()
{
	LookAt(((GameObject3D*)m_pPlayer)->RefPos());

	if (m_hp <= 0)
	{
		Die();
		m_state = DIE;
	}
	else if (m_state == ATTACKED)
	{
		if (m_stunCount < 0.07)
			m_stunCount += DELTATIME;
		else
		{
			m_stunCount = 0.f;
			m_state = WALK;
		}
	}
	else if ((m_pos - ((GameObject3D*)m_pPlayer)->RefPos()).Length() < 30.f)
	{
		m_state = ATTACK;
		Attack();
	}
	else
	{
		Walk();
	}
}

void Monster::Collision(GameObject3D * other)
{
	if (other->GetTag() == "bullet")
	{
		m_hp -= 1.f;
		if (m_state != DIE)
		{
			m_state = ATTACKED;
			m_pSurface = SurfaceManager::Instance()->GetSurface("monster_attacked")->at(0);
		}
	}
}

void Monster::Render()
{
	GameObject3D::Render();
}

void Monster::Walk()
{
	int i = SDL_GetTicks() / 100 % 4;
	m_pSurface = SurfaceManager::Instance()->GetSurface("monster_walk")->at(i);
	Vec3 velocity = (((GameObject3D*)m_pPlayer)->RefPos() - m_pos).Normalize() * m_moveSpeed;
	m_force.RefVelocity() = Vec3(velocity.x, 0.f, velocity.z);
	m_force.Update();
}

void Monster::Attack()
{
	int i = SDL_GetTicks() / 100 % 3;
	m_pSurface = SurfaceManager::Instance()->GetSurface("monster_attack")->at(i);
	if (i == 2 && m_bIsAttack == false) {
		((Player*)m_pPlayer)->Attacked();
		m_bIsAttack = true;
	}
	else if(i != 2){
		m_bIsAttack = false;
	}
}

void Monster::Die()
{
	if(m_state != DIE)
		m_dieCount = SDL_GetTicks();
	Uint32 i = SDL_GetTicks() - m_dieCount;
	i = i / 100 % 13;
	if(i < 5)
		m_pSurface = SurfaceManager::Instance()->GetSurface("monster_die")->at(i);
	else if (i > 11) {
		m_pGameState->Destroy3DGameObject(this);
		s_monsterCount--;
	}

}
