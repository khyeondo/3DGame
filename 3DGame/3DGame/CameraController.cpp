#include "CameraController.h"
#include "InputHandler.h"
#include "Camera.h"


CameraController::CameraController(Camera* pCamera)
{
	m_pCamera = pCamera;
	Init();
}

void CameraController::Init()
{
	Matrix4X4::MakeRotationY(m_rotateLeft,  0.1f);
	Matrix4X4::MakeRotationY(m_rotateRight,-0.1f);
	Matrix4X4::MakeRotationY(m_right, -M_PI / 2.f);
}

void CameraController::Update()
{
	handleInput();
	m_lookDir = m_pCamera->lookAt - m_pCamera->pos;
	m_lookDir.Normalize();
}

void CameraController::Render()
{
}

void CameraController::handleInput()
{
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_W))
	{
		m_pCamera->pos += m_lookDir;
		m_pCamera->lookAt += m_lookDir;
	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_S))
	{
		m_pCamera->pos -= m_lookDir;
		m_pCamera->lookAt -= m_lookDir;
	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_Z))
	{
		m_pCamera->pos.y += 20.f*DELTATIME;
		m_pCamera->lookAt.y += 20.f*DELTATIME;
	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_X))
	{
		m_pCamera->pos.y -= 1.f;
		m_pCamera->lookAt.y -= 1.f;
	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_A))
	{
		Vec3 right;
		right = m_lookDir * m_right;
		m_pCamera->pos -= right;
		m_pCamera->lookAt -= right;
	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_D))
	{
		Vec3 right;
		right = m_lookDir * m_right;
		m_pCamera->pos += right;
		m_pCamera->lookAt += right;
	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_RIGHT))
	{
		Vec3 lookDir = m_pCamera->lookAt - m_pCamera->pos;
		lookDir *= m_rotateRight;
		lookDir += m_pCamera->pos;
		m_pCamera->lookAt = lookDir;
	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_LEFT))
	{
		Vec3 lookDir = m_pCamera->lookAt - m_pCamera->pos;
		lookDir *= m_rotateLeft;
		lookDir += m_pCamera->pos;
		m_pCamera->lookAt = lookDir;
	}
}