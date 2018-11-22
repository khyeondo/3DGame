#pragma once

#include "GameObject.h"
#include "Matrix4X4.h"
#include "Vec3.h"

class Camera;

class CameraController : public GameObject
{
private:
	Camera* m_pCamera;
	Matrix4X4 m_rotateRight;

	Matrix4X4 m_right;

	Vec3 m_lookDir;

	bool mouseLock = true;

public:
	CameraController(Camera* pCamera);

	void RotateY(float angle);

	virtual void Init(GameState* pGameState);
	virtual void Update(GameState* gameState);
	virtual void Render();
	void handleInput(GameState* pGameState);
};