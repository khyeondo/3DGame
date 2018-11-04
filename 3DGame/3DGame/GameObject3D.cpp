
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

void GameObject3D::Init()
{
}

void GameObject3D::Update()
{
}

void GameObject3D::Render()
{
	Renderer3D::Instance()->Rendering(this);
}
