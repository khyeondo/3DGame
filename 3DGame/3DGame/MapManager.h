#pragma once

#include "GameObject3D.h"
#include "Mesh.h"
#include "Color.h"
#include <vector>

#define MAPSIZEX 20
#define MAPSIZEZ 20
#define MAPHEIGHT 6 

using namespace std;

class MapManager : public GameObject3D
{
private:
	vector<GameObject*> m_mapTiles;
	Mesh m_tile;

	GameState* m_pGameState;

	Uint32 m_spawnCount;

private:
	void SetTile(Vec3 pos, Vec3 angle, SDL_Surface* surface, SDL_Surface* nomalMap);
	void SetTile(Vec3 pos, Vec3 angle, Color color);

public:
	MapManager();
	~MapManager() {
		GameObject3D::~GameObject3D();
	}
	virtual void Init(GameState* pGameState);
	virtual void Update();
	virtual void Render();
	virtual void Clean();
};