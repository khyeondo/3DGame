#pragma once

#include "GameObject.h"
#include "Mesh.h"
#include <vector>

using namespace std;

class MapManager : public GameObject
{
private:
	vector<GameObject*> m_mapTiles;
	Mesh m_tile;

public:
	MapManager();
	virtual void Init();
	virtual void Update();
	virtual void Render();
};