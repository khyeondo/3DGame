#pragma once

#include "GameObject3D.h"
#include "Collider.h"
#include "Force.h"

enum MonsterState
{
	WALK,
	ATTACK,
	ATTACKED,
	DIE
};

class Monster : public GameObject3D
{
public:
	Monster(SDL_Surface* surface, SDL_Surface* normalMap, Mesh* mesh);

	virtual void Init(GameState* pGameState);
	virtual void Update();
	virtual void Collision(GameObject3D *other);
	virtual void Render();

	void Walk();
	void Attack();
	void Die();

	static int GetMonsterCount() {
		return s_monsterCount;
	}
private:
	Collider m_collider;
	Force m_force;

	GameObject* m_pPlayer;
	GameState* m_pGameState;

	MonsterState m_state = WALK;

	float m_moveSpeed;
	int m_hp;
	Uint32 m_dieCount = 0;
	float m_stunCount = 0.f;

	static int s_monsterCount; 

};
