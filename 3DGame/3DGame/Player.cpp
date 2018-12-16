#include "Player.h"
#include "InputHandler.h"
#include "Camera.h"
#include "Vec2.h"
#include "Game.h"
#include "GameState.h"
#include "Bullet.h"
#include "MapManager.h"
#include "SurfaceManager.h"
#include "MeshManager.h"
#include "Menu.h"
#include "GameStateMachine.h"

Player::Player(Camera* pCamera):
	GameObject3D(NULL,NULL,NULL), m_collision(this),m_light(this)
{
	m_pCamera = pCamera;
	m_collision.SetCollisionRange(5.f, 5.f);
	m_light.color = { 255, 255, 255 };
	m_light.brightness = 1.f;
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
	m_tag = "player";
	m_pGameState = pGameState;
	Matrix4X4::MakeRotationY(m_rotateRight, -M_PI / 2.f);
	m_pCamera->pos = m_pos;
	m_pCamera->lookAt = m_pos + Vec3(0.f, 0.f, 1.f);
	SDL_ShowCursor(0);
}

void Player::Update()
{
	handleInput();

	if (m_mouseLock) 
	{
		//카메라 회전
		RotateY(-(InputHandler::Instance()->getMousePosition()->x - Game::Instance()->GetScreenWidth() / 2) / 500.f);
		//마우스 위치 고정
		SDL_WarpMouseInWindow(Game::Instance()->GetSDLWindow(),
			Game::Instance()->GetScreenWidth() / 2.f, Game::Instance()->GetScreenHeight() / 2.f);
	}

	m_pos = m_pCamera->pos;
	m_lookDir = m_pCamera->lookAt - m_pCamera->pos;
	m_lookDir.Normalize();

	if (m_hp <= 0)
		GameStateMachine::Instance()->changeState(new Menu());
}

void Player::Render()
{
}

void Player::Collision(GameObject3D * other)
{
}

void Player::Clean()
{
	SDL_ShowCursor(1);
}

void Player::handleInput()
{
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_W))
	{
		//m_pCamera->pos += m_lookDir*DELTATIME*20.f;
		//m_pCamera->lookAt += m_lookDir*DELTATIME*20.f;
		Move(m_lookDir);
	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_S))
	{
		//m_pCamera->pos -= m_lookDir * DELTATIME*20.f;
		//m_pCamera->lookAt -= m_lookDir * DELTATIME*20.f;
		Vec3 moveDir = Vec3(0.f, 0.f, 0.f) - m_lookDir;
		Move(moveDir);
	}
	//if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_Z))
	//{
	//	m_pCamera->pos.y += 20.f*DELTATIME;
	//	m_pCamera->lookAt.y += 20.f*DELTATIME;
	//}
	//if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_X))
	//{
	//	m_pCamera->pos.y -= 20.f*DELTATIME;
	//	m_pCamera->lookAt.y -= 20.f*DELTATIME;
	//}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_A))
	{
		Vec3 moveDir;
		moveDir = m_lookDir * m_rotateRight;
		moveDir = Vec3(0.f, 0.f, 0.f) - moveDir;
		//m_pCamera->pos -= right * DELTATIME*20.f;
		//m_pCamera->lookAt -= right * DELTATIME*20.f;;
		Move(moveDir);
	}
	if (TheInputHandler::Instance()->isKeyHolding(SDL_SCANCODE_D))
	{
		Vec3 moveDir;
		moveDir = m_lookDir * m_rotateRight;
		//m_pCamera->pos += right * DELTATIME*20.f;
		//m_pCamera->lookAt += right * DELTATIME*20.f;
		Move(moveDir);
	}
	if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
	{
		if (m_mouseLock == true)
		{
			Uint32 curTicks = SDL_GetTicks();
			if (curTicks - (m_shootTimer) >= m_shootDelay * 1000.f)
			{
				m_shootTimer = curTicks;
				Bullet* pBullet = new Bullet(
					SurfaceManager::Instance()->GetSurface("bullet")->at(0), NULL,
					MeshManager::Instance()->GetMesh("plane"));
				pBullet->SetDir(m_lookDir*300.f);
				Vec3 pos = m_pos;
				pos.y -= 3.f;
				m_pGameState->GameObject3DInstantiate(pBullet, pos,
					Vec3(-M_PI / 2.f, 0.f, 0.f));
			}
		}
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		if (m_mouseLock) {
			m_mouseLock = false;
			SDL_ShowCursor(1);
			DeltaTime::Instance()->SetGameSpeed(0.f);
		}
		else {
			m_mouseLock = true;
			SDL_ShowCursor(0);
			DeltaTime::Instance()->SetGameSpeed(1.f);
		}
	}
}

void Player::Attacked()
{
	if(m_mouseLock)
		m_hp -= 1;
}

void Player::Move(Vec3 vec)
{
	////m_pCamera->lookAt += vec * DELTATIME*m_moveSpeed;
	//if (m_pCamera->pos.x > MAPSIZEX * 10)
	//{
	//	m_pCamera->pos.x = MAPSIZEX * 10;
	//	m_pCamera->lookAt.z += vec.z;
	//}
	//else if (m_pCamera->pos.x < 0)
	//{
	//	m_pCamera->pos.x = 0.f;
	//	m_pCamera->lookAt.z += vec.z;
	//}
	//else
	//	m_pCamera->lookAt += vec * DELTATIME*m_moveSpeed;
	//if (m_pCamera->pos.z > MAPSIZEZ * 10)
	//{
	//	m_pCamera->pos.z = MAPSIZEZ * 10;
	//	m_pCamera->lookAt.x += vec.z;
	//}
	//else if (m_pCamera->pos.z < 0)
	//{
	//	m_pCamera->pos.z = 0.f;
	//	m_pCamera->lookAt.x += vec.z;
	//}
	m_pCamera->pos += vec * DELTATIME*m_moveSpeed;
	if (m_pCamera->pos.x < MAPSIZEX * 10 && m_pCamera->pos.x > 0.f)
	{
		//m_pCamera->pos.x += vec.x * DELTATIME*m_moveSpeed;
		m_pCamera->lookAt.x += vec.x * DELTATIME*m_moveSpeed;
	}

	if (m_pCamera->pos.z < MAPSIZEZ * 10 && m_pCamera->pos.z > 0.f)
	{
		//m_pCamera->pos.z += vec.z * DELTATIME*m_moveSpeed;
		m_pCamera->lookAt.z += vec.z * DELTATIME*m_moveSpeed;
	}

	m_pCamera->pos.x = MAPSIZEX * 10 > m_pCamera->pos.x ? m_pCamera->pos.x : MAPSIZEX * 10;
	m_pCamera->pos.x = 0.f > m_pCamera->pos.x ? 0.f : m_pCamera->pos.x;
	m_pCamera->pos.z = MAPSIZEZ * 10 > m_pCamera->pos.z ? m_pCamera->pos.z : MAPSIZEZ * 10;
	m_pCamera->pos.z = 0.f > m_pCamera->pos.z ? 0.f : m_pCamera->pos.z;
}
