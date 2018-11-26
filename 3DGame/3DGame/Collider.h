#pragma once

class GameObject3D;
class GameObject;

class Collider
{
private:
	GameObject3D* m_pGameObject;

	float m_radius = 0.f;
	float m_height = 0.f;

public:
	Collider(GameObject3D* pGameObject);
	~Collider();

	friend class ColliderManager;

	void SetCollsionRange(float radius, float height) {
		m_radius = radius;
		m_height = height;
	}

	GameObject3D* GetGameObject() {
		return m_pGameObject;
	}
};