#pragma once

#include "GameObject.h"

class Camera;

class CameraManger : GameObject
{
private:
	Camera* m_pCamera;
	Matrix4X4 rotateX;
	Matrix4X4 rotateY;

public:
	CameraManger(Camera* pCamera);

	virtual void Init();
	virtual void Update();
	virtual void Render();
	void handleInput();
};