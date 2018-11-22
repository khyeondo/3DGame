#include "Menu.h"
#include <iostream>

Menu* Menu::s_pInstance = 0;
const std::string Menu::s_menuID = "MENU";

void Menu::update()
{
	// nothing for now
}

void Menu::render()
{
	// nothing for now
}

bool Menu::onEnter()
{
	std::cout << "entering Menu\n";
	return true;
}

bool Menu::onExit()
{
	std::cout << "exiting Menu\n";
	return true;
}