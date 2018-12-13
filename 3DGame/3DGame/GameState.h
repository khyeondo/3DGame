#pragma once

#include<string>
#include <vector>
#include "Vec3.h"
#include "Vec2.h"

class GameObject;

class GameState
{
protected:
	std::vector<GameObject*> m_3DGameObjects;
	std::vector<GameObject*> m_2DGameObjects;
	std::vector<GameObject*> m_UIGameObjects;

public:
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual std::string getStateID() const = 0;

	void Clean();

	void GameObject3DInstantiate(GameObject* pGameObject,
		Vec3 pos = Vec3(0.f, 0.f, 0.f), Vec3 angle = Vec3(0.f, 0.f, 0.f), Vec3 scale = Vec3(1.f, 1.f, 1.f));
	void GameObject2DInstantiate(GameObject* pGameObject);
	void GameObjectUIInstantiate(GameObject* pGameObject);

	bool Destroy3DGameObject(GameObject* pGameObject);
	bool Destroy2DGameObject(GameObject* pGameObject);
	bool DestroyUIGameObject(GameObject* pGameObject);

	GameObject* Find3DObjectWithTag(std::string tag);
	GameObject* Find2DObjectWithTag(std::string tag);
	GameObject* FindUIObjectWithTag(std::string tag);

};