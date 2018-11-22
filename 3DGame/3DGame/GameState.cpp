#include "GameState.h"
#include "GameObject3D.h"
#include "GameObject2D.h"

void GameState::GameObject3DInstantiate(GameObject * pGameObject, Vec3 pos, Vec3 angle, Vec3 scale)
{
	((GameObject3D*)pGameObject)->RefPos() = pos;
	((GameObject3D*)pGameObject)->RefAngle() = angle;
	((GameObject3D*)pGameObject)->RefScale() = scale;

	m_gameObjects.push_back(pGameObject);
}

void GameState::GameObject2DInstantiate(GameObject * pGameObject, Vec2 pos)
{
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
