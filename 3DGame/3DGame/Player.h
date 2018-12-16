#pragma once

#include "GameObject3D.h"
#include "Matrix4X4.h"
#include "Vec3.h"
#include "Collider.h"
#include "Light.h"
class Camera;

class Player : public GameObject3D
{
private:
	Camera* m_pCamera;
	Matrix4X4 m_rotateRight;
	Vec3 m_lookDir;
	GameState* m_pGameState;

	bool m_mouseLock = true;

	float m_shootDelay = 0.2f;
	Uint32 m_shootTimer = 0.f;

	Collider m_collision;
	Light m_light;

	float m_moveSpeed = 30.f;
	int m_hp = 10;

public:
	Player(Camera* pCamera);
	~Player() {
		GameObject3D::~GameObject3D();
	}

	void RotateY(float angle);

	virtual void Init(GameState* pGameState);
	virtual void Update();
	virtual void Render();
	virtual void Collision(GameObject3D* other);
	virtual void Clean();
	void handleInput();

	void Attacked();
	void Move(Vec3 vec);
	int GetHp() {
		return m_hp;
	}
};