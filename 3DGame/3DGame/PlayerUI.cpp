#include "PlayerUI.h"
#include "Player.h"
#include "GameState.h"
#include "InputHandler.h"
#include "TextureManager.h"

void PlayerUI::Init(GameState * pGameState)
{
	m_pPlayer = pGameState->Find3DObjectWithTag("player");
}

void PlayerUI::Update()
{
	m_currentFrame = 0;
	if (InputHandler::Instance()->getMouseButtonState(LEFT)) {
		m_currentFrame = (SDL_GetTicks() / 50) % 2 + 1;
	}
}

void PlayerUI::Render()
{	
	TextureManager::Instance()->draw("aim",385,285,30,30);
	TextureManager::Instance()->draw("hp", -20, 520, 100, 100);
	TextureManager::Instance()->draw("hp_bar", 85, 545,
		170.f*((float)((Player*)m_pPlayer)->GetHp()/10.f), 40);
	GameObject2D::Render();
}
