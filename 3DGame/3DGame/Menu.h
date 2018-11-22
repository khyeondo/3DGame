#pragma once
#include"GameState.h"
class Menu : public GameState
{
public:
	virtual void init();
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_menuID; }

	static Menu* Instance() {
		if (s_pInstance == 0)
			s_pInstance = new Menu;
		return s_pInstance;
	}
private:
	static const std::string s_menuID;
	static Menu* s_pInstance;
};