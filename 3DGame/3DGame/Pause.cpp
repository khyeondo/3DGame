#include "Pause.h"
#include "InputHandler.h"

void Pause::Init(GameState * pGameState)
{
}

void Pause::Update()
{
	m_currentFrame = 0;
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE) && m_bPause == false) {
		m_bPause = true;
	}
	else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE) && m_bPause == true) {
		m_bPause = false;
	}
}

void Pause::Render()
{
	if (m_bPause == true)
		GameObject2D::Render();
}
