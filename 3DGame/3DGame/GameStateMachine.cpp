#include "GameStateMachine.h"

GameStateMachine* GameStateMachine::s_pInst = 0;

void GameStateMachine::changeState(GameState *pState)
{
	if (pState != NULL)
	{
		if (m_currentState != NULL) {
			m_prevState = m_currentState;
			m_currentState->onExit();
		}
		m_currentState = pState;
		m_currentState->onEnter();
		m_currentState->init();
	}
}

void GameStateMachine::Update()
{
	if (m_currentState != NULL)
		m_currentState->update();
}

void GameStateMachine::Render()
{
	if (m_currentState != NULL)
		m_currentState->render();
}