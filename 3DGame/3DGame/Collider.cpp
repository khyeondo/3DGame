#include "Collider.h"
#include "CollideManger.h"

using namespace std;

Collider::Collider(GameObject3D * pGameObject) :
	m_pGameObject(pGameObject)
{
	ColliderManager::Instance()->m_colliders.push_back(this);
}

Collider::~Collider()
{
	ColliderManager::Instance()->DestroyCollider(this);
}
