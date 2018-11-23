#include "GameState.h"
#include "GameObject.h"
#include "GameObject3D.h"
#include "GameObject2D.h"

void GameState::GameObject3DInstantiate(GameObject * pGameObject, Vec3 pos, Vec3 angle, Vec3 scale)
{
	((GameObject3D*)pGameObject)->RefPos() = pos;
	((GameObject3D*)pGameObject)->RefAngle() = angle;
	((GameObject3D*)pGameObject)->RefScale() = scale;

	m_gameObjects.push_back(pGameObject);
	pGameObject->Init(this);
}

void GameState::GameObject2DInstantiate(GameObject * pGameObject, Vec2 pos)
{
}

void GameState::DestroyGameObject(GameObject * pGameObject)
{
	vector<GameObject*>::iterator iter = m_gameObjects.begin();
	vector<GameObject*>::iterator iterEnd = m_gameObjects.end();

	for (; iter != iterEnd; iter++)
	{
		if (*iter == pGameObject)
		{
			m_gameObjects.erase(iter);
			delete (GameObject3D*)pGameObject;
			return;
		}
	}
}

GameObject * GameState::FindObjectByTag(std::string tag)
{
	for (GameObject* gameObejct : m_gameObjects)
	{
		if (gameObejct->GetTag() == tag)
			return gameObejct;
	}
	return NULL;
}
