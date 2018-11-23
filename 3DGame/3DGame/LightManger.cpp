#include"LightManger.h"

LightManager* LightManager::s_pinst = 0;

void LightManager::Destroy(Light * pLight)
{
	vector<Light*>::iterator iter = m_lights.begin();
	vector<Light*>::iterator iterEnd = m_lights.end();

	for (; iter != iterEnd; iter++)
	{
		if (*iter == pLight)
		{
			m_lights.erase(iter);
			return;
		}
	}
}
