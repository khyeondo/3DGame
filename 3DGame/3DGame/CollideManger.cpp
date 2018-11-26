#include "CollideManger.h"
#include "Collider.h"
#include "GameObject3D.h"
#include "Vec3.h"

ColliderManager* ColliderManager::s_pinst = 0;

bool ColliderManager::CollisionCheck(Collider * col1, Collider * col2)
{
	//원기둥 모양의 충돌체 검사
	float dx = col1->m_pGameObject->RefPos().x - col2->m_pGameObject->RefPos().x;
	float dz = col1->m_pGameObject->RefPos().z - col2->m_pGameObject->RefPos().z;
	float dist = sqrt(dx * dx + dz * dz);

	if (dist > col1->m_radius + col2->m_radius)
		return false;


	float top1, bottom1, top2, bottom2;
	top1 = col1->m_pGameObject->RefPos().y + col1->m_height / 2.f;
	bottom1 = top1 - col1->m_height;

	top2 = col2->m_pGameObject->RefPos().y + col1->m_height / 2.f;
	bottom2 = top2 - col2->m_height;

	if (top1 < bottom2 && bottom1 > top2)
		return false;

	return true;
}

void ColliderManager::Update()
{
	//list<Collider*>::iterator iter1 = m_colliders.begin();
	//list<Collider*>::iterator iter2;
	//list<Collider*>::iterator iterEnd = m_colliders.end();

	for (int i = 0; i < m_colliders.size() - 1; i++)
	{
		//iter2 = iter1;
		//iter2++;
		for (int j = i + 1; j < m_colliders.size(); j++)
		{
			if (CollisionCheck(m_colliders[i], m_colliders[j]))
			{
				m_colliders[i]->m_pGameObject->Collision(m_colliders[j]->m_pGameObject);
				m_colliders[j]->m_pGameObject->Collision(m_colliders[i]->m_pGameObject);
			}
			//iter2++;
		}
		//iter1++;
	}
}

void ColliderManager::Clear()
{
	m_colliders.clear();
}

void ColliderManager::DestroyCollider(Collider * col)
{
	vector<Collider*>::iterator iter = m_colliders.begin();
	vector<Collider*>::iterator iterEnd = m_colliders.end();
	
	for (; iter != iterEnd; iter++)
	{
		if (*iter == col)
		{
			m_colliders.erase(iter);
			return;
		}
	}
}
