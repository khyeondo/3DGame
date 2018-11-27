#pragma once
#include "GameState.h"
class GameStateMachine
{
private:
	GameStateMachine() {}
	static GameStateMachine* s_pInst;

public: 
	static GameStateMachine* Instance() {
		if(s_pInst == 0)
			s_pInst = new GameStateMachine();
		return s_pInst;
	}

public:
	void changeState(GameState* pState);

	void Update();
	void Render();

private:
	
	GameState* m_currentState;
	GameState* m_prevState;

};