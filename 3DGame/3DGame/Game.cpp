#include <iostream>
#include "Game.h"
#include "Vec2.h"
#include "Renderer3D.h"
#include "Camera.h"
#include "GameObject3D.h"

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
	//mesh.LoadFromObjectFile("assets/teaPot.obj",true);
	mesh.SetCube(Vec3(5.f, 5.f, 5.f), Vec3(10, 10, 10));
	//mesh.LoadFromObjectFile("assets/teaPot.obj");

	for (int i = 0; i < 12; i += 2)
	{
		mesh.polys[i].uv[0] = Vec2(0, 1);
		mesh.polys[i].uv[1] = Vec2(0, 0);
		mesh.polys[i].uv[2] = Vec2(1, 1);

		mesh.polys[i + 1].uv[0] = Vec2(1, 1);
		mesh.polys[i + 1].uv[1] = Vec2(0, 0);
		mesh.polys[i + 1].uv[2] = Vec2(1, 0);
	}

	m_pGameObject = new GameObject3D(m_pSurface2, m_pNormal2, &mesh);
	m_pGameObject2 = new GameObject3D(m_pSurface, m_pNormal, &mesh);
	((GameObject3D*)m_pGameObject)->RefPos().x = 10.f;
	((GameObject3D*)m_pGameObject)->RefPos().y = 0.f;
	((GameObject3D*)m_pGameObject)->RefPos().z = 0.f;
}

void Game::handleEvents()
{
	startTick = SDL_GetTicks();
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			isKeyHolding[event.key.keysym.sym % 107374100] = true;
			break;
		case SDL_KEYUP:
			isKeyHolding[event.key.keysym.sym % 107374100] = false;
			break;
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
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

	//((GameObject3D*)m_pGameObject)->RefAngle() += Vec3(0.01f,0.01f, 0.01f);

	if (isKeyHolding[SDLK_a])
	{
		Renderer3D::Instance()->GetCamera()->pos.x -= 0.3f;
		Renderer3D::Instance()->GetCamera()->lookAt.x -= 0.3f;
	}
	if (isKeyHolding[SDLK_d])
	{
		Renderer3D::Instance()->GetCamera()->pos.x += 0.3f;
		Renderer3D::Instance()->GetCamera()->lookAt.x += 0.3f;
	}
	if (isKeyHolding[SDLK_w])
	{
		Renderer3D::Instance()->GetCamera()->pos.z += 0.3f;
		Renderer3D::Instance()->GetCamera()->lookAt.z += 0.3f;
	}
	if (isKeyHolding[SDLK_s])
	{
		Renderer3D::Instance()->GetCamera()->pos.z -= 0.3f;
		Renderer3D::Instance()->GetCamera()->lookAt.z -= 0.3f;
	}
	if (isKeyHolding[SDLK_z])
	{
		Renderer3D::Instance()->GetCamera()->pos.y += 0.30f;
		Renderer3D::Instance()->GetCamera()->lookAt.y += 0.30f;
	}
	if (isKeyHolding[SDLK_x])
	{
		Renderer3D::Instance()->GetCamera()->pos.y -= 0.30f;
		Renderer3D::Instance()->GetCamera()->lookAt.y -= 0.30f;
	}
	if (isKeyHolding[SDLK_UP % 107374100])
	{
		Renderer3D::Instance()->GetCamera()->lookAt.y -= 0.30f;
	}
	if (isKeyHolding[SDLK_DOWN % 107374100])
	{
		Renderer3D::Instance()->GetCamera()->lookAt.y += 0.30f;
	}
	if (isKeyHolding[SDLK_LEFT % 107374100])
	{
		Renderer3D::Instance()->GetCamera()->lookAt.x -= 3.30f;
	}
	if (isKeyHolding[SDLK_RIGHT % 107374100])
	{
		Renderer3D::Instance()->GetCamera()->lookAt.x += 3.30f;
	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 255, 255);
	SDL_RenderClear(m_pRenderer);

	m_pGameObject->Render();
	m_pGameObject2->Render();

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
