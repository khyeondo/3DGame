#pragma once
#include "GameState.h"
class GameStateMachine
{
public:
	void changeState(GameState* pState);

	void Update();
	void Render();

private:
	GameState* m_currentState;
	GameState* m_prevState;

};