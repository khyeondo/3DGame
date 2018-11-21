#pragma once

#include "GameObject.h"
#include "Matrix4X4.h"
#include "Vec3.h"

class Camera;

class CameraController : public GameObject
{
private:
	Camera* m_pCamera;
	Matrix4X4 m_rotateLeft;
	Matrix4X4 m_rotateRight;

	Matrix4X4 m_rotateX;
	Matrix4X4 m_rotateY;

	Matrix4X4 m_right;

	Vec3 m_lookDir;

public:
	CameraController(Camera* pCamera);

	void RotateY(float angle);

	virtual void Init();
	virtual void Update();
	virtual void Render();
	void handleInput();
};