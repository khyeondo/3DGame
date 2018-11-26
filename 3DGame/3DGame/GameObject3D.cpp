
#include "GameObject3D.h"
#include "Renderer3D.h"
#include "Mesh.h"

GameObject3D::GameObject3D(SDL_Surface * surface, SDL_Surface * normalMap, Mesh * mesh) :
	GameObject(), m_pSurface(surface), m_pNormalMap(normalMap), m_pMesh(mesh)
{
	if (surface == 0)
		m_pPainter = &(Renderer3D::Instance()->m_colorPainter);
	else
		m_pPainter = &(Renderer3D::Instance()->m_texturePainter);

	if (normalMap == 0)
		m_pShader = &(Renderer3D::Instance()->m_flatShader);
	else
		m_pShader = &(Renderer3D::Instance()->m_plxelShader);
}

GameObject3D::GameObject3D(Color color, Mesh * mesh) : 
	GameObject(), m_pSurface(NULL), m_pNormalMap(NULL), m_pMesh(mesh)
{
	m_pPainter = &(Renderer3D::Instance()->m_colorPainter);
	m_pShader = &(Renderer3D::Instance()->m_flatShader);
	m_color = color;
}

void GameObject3D::Init(GameState* pGameState)
{
}

void GameObject3D::Update()
{
}

void GameObject3D::Collision(GameObject3D * other)
{
}

void GameObject3D::Render()
{
	Renderer3D::Instance()->Rendering(this);
}

void GameObject3D::LookAt(Vec3 vec)
{
	Vec3 direction = m_pos - vec;
	m_lookAngle.y = atan2(direction.z, direction.x) - M_PI/2.f;
}
