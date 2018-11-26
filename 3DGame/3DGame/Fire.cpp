#include "Fire.h"
#include "Camera.h"
#include "SurfaceManager.h"
Fire::Fire(SDL_Surface * surface, SDL_Surface * normalMap, Mesh * mesh) :
	GameObject3D(surface,normalMap,mesh),m_light(this)
{
	m_tag = "fire";
	m_light.brightness = 2.f;
	m_light.color = Color(198, 102, 3);
	m_angle = Vec3(M_PI / 2.f, M_PI, 0.f);
	m_scale = Vec3(15.f, 15.f, 15.f);
}

void Fire::Init(GameState * pGameState)
{

}

void Fire::Update()
{
	LookAt(Renderer3D::Instance()->GetCamera()->pos);

	int i = SDL_GetTicks()/30 % 9;
	m_pSurface = SurfaceManager::Instance()->GetSurface("fire")->at(i);
}

void Fire::Render()
{
	if (SDL_GetTicks() % 6 == 0)
	{
		m_light.color = Color(198, 102, 3);
		m_light.brightness = 2.5f;
	}
	else if (SDL_GetTicks() % 5 == 0)
	{
		m_light.color = Color(217, 145, 15);
		m_light.brightness = 2.0f;
	}
	else if (SDL_GetTicks() % 10 == 0)
	{
		m_light.color = Color(237, 196, 56);
		m_light.brightness = 2.3f;
	}
	GameObject3D::Render();
}
