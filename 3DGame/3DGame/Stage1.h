#pragma once

#include "GameState.h"

class Stage1 : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_Stage1ID; }

	static Stage1* Instance() {
		if (s_pInstance == 0)
			s_pInstance = new Stage1;
		return s_pInstance;
	}
private:
	static const std::string s_Stage1ID;
	static Stage1* s_pInstance;
};