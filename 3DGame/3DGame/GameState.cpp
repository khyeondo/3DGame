#include "GameState.h"
#include "GameObject.h"
#include "GameObject3D.h"
#include "GameObject2D.h"

void GameState::Clean()
{
	for (GameObject* pGameObject : m_3DGameObjects) {
		pGameObject->Clean();
		delete pGameObject;
	}
	for (GameObject* pGameObject : m_2DGameObjects) {
		pGameObject->Clean();
		delete pGameObject;
	}
	for (GameObject* pGameObject : m_UIGameObjects) {
		pGameObject->Clean();
		delete pGameObject;
	}
	m_3DGameObjects.clear();
	m_2DGameObjects.clear();
	m_UIGameObjects.clear();
}

void GameState::GameObject3DInstantiate(GameObject * pGameObject, Vec3 pos, Vec3 angle, Vec3 scale)
{
	((GameObject3D*)pGameObject)->RefPos() = pos;
	((GameObject3D*)pGameObject)->RefAngle() = angle;
	((GameObject3D*)pGameObject)->RefScale() = scale;

	pGameObject->Init(this);
	m_3DGameObjects.push_back(pGameObject);
}

void GameState::GameObject2DInstantiate(GameObject * pGameObject)
{
	((GameObejct2D*)pGameObject);

	pGameObject->Init(this);
	m_2DGameObjects.push_back(pGameObject);
}

void GameState::GameObjectUIInstantiate(GameObject * pGameObject)
{
	pGameObject->Init(this);
	m_UIGameObjects.push_back(pGameObject);
}

bool GameState::Destroy3DGameObject(GameObject * pGameObject)
{
	vector<GameObject*>::iterator iter = m_3DGameObjects.begin();
	vector<GameObject*>::iterator iterEnd = m_3DGameObjects.end();

	for (; iter != iterEnd; iter++)
	{
		if (*iter == pGameObject)
		{
			m_3DGameObjects.erase(iter);
			delete (GameObject3D*)pGameObject;
			return true;
		}
	}
	return false;
}

bool GameState::Destroy2DGameObject(GameObject * pGameObject)
{
	vector<GameObject*>::iterator iter = m_2DGameObjects.begin();
	vector<GameObject*>::iterator iterEnd = m_2DGameObjects.end();

	for (; iter != iterEnd; iter++)
	{
		if (*iter == pGameObject)
		{
			m_2DGameObjects.erase(iter);
			delete (GameObject3D*)pGameObject;
			return true;
		}
	}
	return false;
}

bool GameState::DestroyUIGameObject(GameObject * pGameObject)
{
	vector<GameObject*>::iterator iter = m_UIGameObjects.begin();
	vector<GameObject*>::iterator iterEnd = m_UIGameObjects.end();

	for (; iter != iterEnd; iter++)
	{
		if (*iter == pGameObject)
		{
			m_UIGameObjects.erase(iter);
			delete (GameObject3D*)pGameObject;
			return true;
		}
	}
	return false;
}

GameObject * GameState::Find3DObjectByTag(std::string tag)
{
	for (GameObject* gameObejct : m_3DGameObjects)
	{
		if (gameObejct->GetTag() == tag)
			return gameObejct;
	}
	return NULL;
}

GameObject * GameState::Find2DObjectByTag(std::string tag)
{
	for (GameObject* gameObejct : m_2DGameObjects)
	{
		if (gameObejct->GetTag() == tag)
			return gameObejct;
	}
	return NULL;
}

GameObject * GameState::FindUIObjectByTag(std::string tag)
{
	for (GameObject* gameObejct : m_UIGameObjects)
	{
		if (gameObejct->GetTag() == tag)
			return gameObejct;
	}
	return NULL;
}
