#include <iostream>
#include "Game.h"
#include "Vec2.h"
#include "Renderer3D.h"
#include "Camera.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "Menu.h"

Game* Game::m_pinst = 0;

bool Game::init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		m_pWindow = SDL_CreateWindow(title,
			xpos, ypos,
			width, height, SDL_WINDOW_SHOWN && fullscreen);
	}

	if (m_pWindow != 0)
	{
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
	}
	else
	{
		m_bRunning = false;
		return false;
	}

	m_bRunning = true;

	screenWidth = width;
	screenHeight = height;

	strcpy_s(windowTitle,20 ,(char*)title);

	m_pCamera = new Camera(Vec3(0.f, 0.f, 0.f), Vec3(0.f, 0.f, -1.f), 1.f, 500.f, 90.f);

	Renderer3D::Instance()->Init(m_pRenderer, m_pCamera, Vec3(0.f, -1.f, 1.f), Color(0,0,0),width, height);

	m_pGameStateMachine = GameStateMachine::Instance();
	m_pGameStateMachine->changeState(new Menu());
	return true;
}

void Game::start()
{
}

void Game::handleEvents()
{
	startTick = SDL_GetTicks(); //프레임 체크
	TheInputHandler::Instance()->update();
}

void Game::update()
{
	m_pGameStateMachine->Update();
}

void Game::render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 255, 255);
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->Render();

	SDL_RenderPresent(m_pRenderer);

	fps = 1000.0f / (float)(SDL_GetTicks() - startTick);
	char cfps[40];

	sprintf_s(cfps,40, "%s  -  FPS : %0.3f", windowTitle , fps);
	SDL_SetWindowTitle(m_pWindow, cfps);
}

void Game::clean()
{
	std::cout << "cleaning game\n";

	delete m_pGameStateMachine;
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
