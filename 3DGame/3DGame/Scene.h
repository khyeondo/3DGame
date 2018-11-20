#pragma once
#include <list>
#include "GameObject.h"

using namespace std;

class Scene
{
protected:
	list<GameObject*> m_GameObjects;

public:
	void Update();
	void Render();
};