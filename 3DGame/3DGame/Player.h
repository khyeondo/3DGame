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

	Matrix4X4 m_right;

	Vec3 m_lookDir;

	bool mouseLock = true;

	float m_shootDeley = 0.2f;
	Uint32 m_shootTimer = 0.f;

	GameState* m_pGameState;

	Collider m_collision;
	Light m_light;

	float m_moveSpeed = 30.f;

public:
	Player(Camera* pCamera);

	void RotateY(float angle);

	virtual void Init(GameState* pGameState);
	virtual void Update();
	virtual void Render();
	virtual void Collision(GameObject3D* other);
	void handleInput();

	void Move(Vec3 vec);
};