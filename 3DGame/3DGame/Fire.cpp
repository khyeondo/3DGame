#include "Fire.h"
#include "Camera.h"
#include "SurfaceManager.h"
Fire::Fire(SDL_Surface * surface, SDL_Surface * normalMap, Mesh * mesh) :
	GameObject3D(surface,normalMap,mesh),m_light(this)
{
	m_tag = "fire";
	m_light.brightness = 0.3f;
	m_light.color = Color(255, 100, 100);
	m_angle = Vec3(M_PI/2.f,M_PI,0.f);
	m_scale = Vec3(15.f, 15.f, 15.f);
}

void Fire::Init(GameState * pGameState)
{
}

void Fire::Update(GameState * pGameState)
{
	if (SDL_GetTicks() % 6 == 0)
	{
		m_light.color = Color(220, 30, 100);
		m_light.brightness = 0.3f;
	}
	else if (SDL_GetTicks() % 5 == 0)
	{
		m_light.color = Color(250, 100, 100);
		m_light.brightness = 0.3f;
	}
	else if (SDL_GetTicks() % 10 == 0)
	{
		m_light.color = Color(255, 120, 120);
		m_light.brightness = 0.4f;
	}
	LookAt(Renderer3D::Instance()->GetCamera()->pos);

	int i = SDL_GetTicks()/30 % 9;
	m_pSurface = SurfaceManager::Instance()->GetSurface("fire")->at(i);
}

void Fire::Render()
{
	GameObject3D::Render();
}
