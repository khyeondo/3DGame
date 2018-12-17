#include "Menu.h"
#include "TextureManager.h"
#include "Button.h"
#include "Stage1.h"
#include "GameStateMachine.h"
#include "Game.h"
#include <iostream>

Menu* Menu::s_pInstance = 0;
const std::string Menu::s_menuID = "MENU";

void Menu::init()
{
}

void Menu::update()
{
	for (int i = 0; i < m_2DGameObjects.size(); i++)
	{
		m_2DGameObjects[i]->Update();
	}
	for (int i = 0; i < m_UIGameObjects.size(); i++)
	{
		m_UIGameObjects[i]->Update();
	}
}

void Menu::render()
{
	for (int i = 0; i != m_2DGameObjects.size(); i++)
	{
		m_2DGameObjects[i]->Render();
	}
	for (int i = 0; i != m_UIGameObjects.size(); i++)
	{
		m_UIGameObjects[i]->Render();
	}
}

bool Menu::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/button.png",
		"playbutton"))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/exit.png",
		"exitbutton"))
	{
		return false;
	}
	GameObject* button1 = new Button(Vec2(200, 150), Vec2(400, 100), "playbutton", s_menuToPlay);

	GameObject* button2 = new Button(Vec2(200, 350), Vec2(400, 100), "exitbutton", s_exitFromMenu);

	GameObjectUIInstantiate(button1);
	GameObjectUIInstantiate(button2);
	return true;
}

bool Menu::onExit()
{
	Clean();
	TextureManager::Instance()->Clear();
	std::cout << "exiting Menu\n";
	return true;
}

void Menu::s_menuToPlay()
{
	GameStateMachine::Instance()->changeState(Stage1::Instance());
}

void Menu::s_exitFromMenu()
{
	Game::Instance()->quit();
}