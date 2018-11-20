#pragma once

class GameObject;

class Collider
{
private:
	GameObject* m_pGameObject;

public:
	Collider(GameObject* pGameObject);

	bool IsCollision(Collider* pCollider);

	GameObject* GetGameObject() {
		return m_pGameObject;
	}
};