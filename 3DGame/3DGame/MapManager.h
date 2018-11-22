#pragma once

#include "GameObject.h"
#include "Mesh.h"
#include "Color.h"
#include <vector>

using namespace std;

class MapManager : public GameObject
{
private:
	vector<GameObject*> m_mapTiles;
	Mesh m_tile;

private:
	void SetTile(Vec3 pos, Vec3 angle, SDL_Surface* surface, SDL_Surface* nomalMap);
	void SetTile(Vec3 pos, Vec3 angle, Color color);

public:
	MapManager();
	virtual void Init();
	virtual void Update();
	virtual void Render();
};