#include "GameObject2D.h"
#include "TextureManager.h"
#include "Game.h"

GameObject2D::~GameObject2D()
{
	GameObject::~GameObject();
}

void GameObject2D::Init(GameState* pGameState)
{
}

void GameObject2D::Update()
{
}

void GameObject2D::Render()
{
	TextureManager::Instance()->drawFrame(m_textureID,
		(int)m_pos.x, (int)m_pos.y,
		(int)m_size.x, (int)m_size.y, m_currentRow, m_currentFrame);
}

void GameObject2D::Clean()
{
}
