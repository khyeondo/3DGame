#include "CameraManger.h"
#include "InputHandler.h"
#include "Matrix4X4.h"

CameraManger::CameraManger(Camera* pCamera)
{
	m_pCamera = pCamera;
	Init();
}

void CameraManger::Init()
{
}

void CameraManger::Update()
{
	handleInput();
}

void CameraManger::Render()
{
}

void CameraManger::handleInput()
{
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_W))
	{
	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_S))
	{

	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_A))
	{

	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_D))
	{

	}
}