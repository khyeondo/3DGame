#pragma once

#include <vector>

class Collider;

class ColliderManager
{
private:
	ColliderManager() {}
	static ColliderManager* s_pinst;

public:
	static ColliderManager* Instance() {
		if (s_pinst == 0)
			s_pinst = new ColliderManager();
		return s_pinst;
	}

private:
	std::vector<Collider*> m_colliders;

public:
	bool CollisionCheck(Collider* col1, Collider*col2);
	void Update();
	void Clear();
	void DestroyCollider(Collider* col);

	friend Collider;
};