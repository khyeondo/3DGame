#include <iostream>
#include "Game.h"
#include "Vec2.h"
#include "Renderer3D.h"
#include "Camera.h"
#include "GameObject3D.h"
#include "InputHandler.h"
#include "CameraController.h"
#include "Cube.h"

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

	m_pCamera = new Camera(Vec3(0.f, 0.f, -30.f), Vec3(1.f, 1.f, -1.f), 1.f, 1000.f, 90.f);

	Renderer3D::Instance()->Init(m_pRenderer, m_pCamera, Vec3(0.f, 0.f, 1.f), Color(200,230, 255),width, height);

	return true;
}

void Game::start()
{
	//m_Surface = SDL_LoadBMP("Assets/animate.bmp");
	m_pSurface = IMG_Load("Assets/DisplacementMap.png");
	m_pNormal = IMG_Load("assets/NormalMap.png");
	m_pSurface2 = IMG_Load("Assets/DisplacementMap2.png");
	m_pNormal2 = IMG_Load("assets/NormalMap2.png");
	m_pSurface3 = IMG_Load("assets/w.png");

	cube.SetCube(Vec3(5.f, 5.f, 5.f), Vec3(10, 10, 10));
	mountains.LoadFromObjectFile("assets/mountains.obj");

	for (int i = 0; i < 12; i += 2)
	{
		cube.polys[i].uv[0] = Vec2(0, 1);
		cube.polys[i].uv[1] = Vec2(0, 0);
		cube.polys[i].uv[2] = Vec2(1, 1);

		cube.polys[i + 1].uv[0] = Vec2(1, 1);
		cube.polys[i + 1].uv[1] = Vec2(0, 0);
		cube.polys[i + 1].uv[2] = Vec2(1, 0);
	}

	m_pCameraController = new CameraController(m_pCamera);
	m_pGameObject = new GameObject3D(m_pSurface2, m_pNormal2, &cube);
	m_pGameObject2 = new GameObject3D(m_pSurface, m_pNormal, &cube);
	m_pGameObject3 = new GameObject3D(m_pSurface3, NULL, &mountains);
	((GameObject3D*)m_pGameObject)->RefPos().x = 13.f;
	((GameObject3D*)m_pGameObject)->RefPos().y = 0.f;
	((GameObject3D*)m_pGameObject)->RefPos().z = 0.f;
	((GameObject3D*)m_pGameObject3)->RefPos().y = -50.f;

	m_gameObjects.push_back(m_pCameraController);
	m_gameObjects.push_back(m_pGameObject);
	m_gameObjects.push_back(m_pGameObject2);
	m_gameObjects.push_back(m_pGameObject3);
	m_gameObjects.push_back(new Cube(m_pSurface3, NULL, &cube));
}

void Game::handleEvents()
{
	startTick = SDL_GetTicks(); //프레임 체크
	TheInputHandler::Instance()->update();
}

void Game::update()
{
	//object.angle += Vec3(0.05f, 0.05f, 0.05f);
	Matrix4X4 rotateX;
	Matrix4X4 rotateY;
	Matrix4X4 rotateZ;
	//Matrix4X4::MakeRotationX(rotateX, 0.1f);
	Matrix4X4::MakeRotationY(rotateY, 0.1f);
	//Matrix4X4::MakeRotationY(rotateZ, 0.07f);
	Renderer3D::Instance()->RefLight() *= rotateY;
	//Renderer3D::Instance()->RefLight() *= rotateX;
	//Renderer3D::Instance()->RefLight() *= rotateZ;

	for (GameObject* gameObject : m_gameObjects)
	{
		gameObject->Update();
	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 255, 255);
	SDL_RenderClear(m_pRenderer);


	for (GameObject* gameObject : m_gameObjects)
	{
		gameObject->Render();
	}

	Renderer3D::Instance()->Present();

	SDL_RenderPresent(m_pRenderer);

	fps = 1000.0f / (float)(SDL_GetTicks() - startTick);
	char cfps[40];

	sprintf_s(cfps,40, "%s  -  FPS : %0.3f", windowTitle , fps);
	SDL_SetWindowTitle(m_pWindow, cfps);
}

void Game::clean()
{
	std::cout << "cleaning game\n";

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
