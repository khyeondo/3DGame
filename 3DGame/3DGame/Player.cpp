#include "Player.h"
#include "InputHandler.h"
#include "Camera.h"
#include "Vec2.h"
#include "Game.h"
#include "GameState.h"
#include "Bullet.h"
#include "SurfaceManager.h"
#include "MeshManager.h"

Player::Player(Camera* pCamera):
	GameObject3D(NULL,NULL,NULL), m_collision(this),m_light(this)
{
	m_pCamera = pCamera;
	m_collision.SetCollsionRage(5.f, 5.f);
	m_light.color = { 255, 255, 255 };
	m_light.brightness = 0.7f;
}

void Player::RotateY(float angle)
{
	Matrix4X4 rotateY;
	Matrix4X4::MakeRotationY(rotateY, angle);

	Vec3 lookDir = m_pCamera->lookAt - m_pCamera->pos;
	lookDir *= rotateY;
	m_pCamera->lookAt = m_pCamera->pos + lookDir;
}

void Player::Init(GameState* pGameState)
{
	Matrix4X4::MakeRotationY(m_right, -M_PI / 2.f);
	SDL_ShowCursor(0);
}

void Player::Update(GameState* pGameState)
{
	handleInput(pGameState);

	if (mouseLock) 
	{
		RotateY(-(InputHandler::Instance()->getMousePosition()->x - Game::Instance()->GetScreenWidth() / 2) / 500.f);
		SDL_WarpMouseInWindow(Game::Instance()->GetSDLWindow(),
			Game::Instance()->GetScreenWidth() / 2.f, Game::Instance()->GetScreenHeight() / 2.f);
	}

	m_lookDir = m_pCamera->lookAt - m_pCamera->pos;
	m_lookDir.Normalize();
	m_pos = m_pCamera->pos;
}

void Player::Render()
{
}

void Player::Collision(GameObject3D * other)
{
}

void Player::handleInput(GameState* pGameState)
{
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_W))
	{
		m_pCamera->pos += m_lookDir*DELTATIME*20.f;
		m_pCamera->lookAt += m_lookDir*DELTATIME*20.f;
	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_S))
	{
		m_pCamera->pos -= m_lookDir * DELTATIME*20.f;
		m_pCamera->lookAt -= m_lookDir * DELTATIME*20.f;
	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_Z))
	{
		m_pCamera->pos.y += 20.f*DELTATIME;
		m_pCamera->lookAt.y += 20.f*DELTATIME;
	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_X))
	{
		m_pCamera->pos.y -= 20.f*DELTATIME;
		m_pCamera->lookAt.y -= 20.f*DELTATIME;
	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_A))
	{
		Vec3 right;
		right = m_lookDir * m_right;
		m_pCamera->pos -= right * DELTATIME*20.f;
		m_pCamera->lookAt -= right * DELTATIME*20.f;;
	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_D))
	{
		Vec3 right;
		right = m_lookDir * m_right;
		m_pCamera->pos += right * DELTATIME*20.f;
		m_pCamera->lookAt += right * DELTATIME*20.f;
	}
	if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
	{
		Uint32 curTicks = SDL_GetTicks();
		if (curTicks - (m_shootTimer) >= m_shootDeley*1000.f)
		{
			m_shootTimer = curTicks;
			Bullet* pBullet = new Bullet(
				SurfaceManager::Instance()->GetSurface("bullet")->at(0), NULL,
				MeshManager::Instance()->GetMesh("plane"));
			pBullet->SetDir(m_lookDir*100.f);
			pGameState->GameObject3DInstantiate(pBullet, m_pCamera->pos + (m_lookDir * 10),
				Vec3(-M_PI / 2.f, 0.f, 0.f));
		}
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		if (mouseLock) {
			mouseLock = false;
			SDL_ShowCursor(1);
		}
		else {
			mouseLock = true;
			SDL_ShowCursor(0);
		}
	}
}