#pragma once

#include "GameObject.h"
#include <vector>

using namespace std;

class MapManager : GameObject
{
private:
	vector<GameObject*> mapTiles;
	char* map;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
};