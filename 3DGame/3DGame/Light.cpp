#include "Light.h"
#include "LightManger.h"
#include "GameObject3D.h"
#include <vector>

Light::Light(GameObject3D* pGameObject):
	pos(pGameObject->RefPos())
{
	number = LightManager::Instance()->m_lights.size();
	LightManager::Instance()->m_lights.push_back(this);
}

Light::~Light()
{
	Delete();
}

void Light::Delete()
{
	LightManager::Instance()->Destroy(this);
}
