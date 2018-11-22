#include "Force.h"
#include "GameObject3D.h"

Force::Force(GameObject3D * gameObject) :
	 m_pGameObject(gameObject)
{
}

void Force::AddForce(Vec3 force)
{
	m_acceleration += force;
}

void Force::Update()
{
	m_velocity += m_acceleration * DELTATIME;
	m_pGameObject->RefPos() += m_velocity * DELTATIME;
}
