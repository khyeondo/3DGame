#include "MapManager.h"
#include "GameObject3D.h"
#include "SurfaceManager.h"

#define MAPSIZEX 20
#define MAPSIZEY 20

MapManager::MapManager()
{
	Init();
}

void MapManager::Init()
{
	char map[][MAPSIZEX*2 + 1] =
	{
	{ "¦£¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¤" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ "¦¦¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦¥" },
	};

	m_tile.SetPlane(Vec3(0.f, 0.f, 0.f), Vec3(10.f, 10.f, 10.f));
	SDL_Surface* surface = SurfaceManager::Instance()->GetSurface("box");

	Color tileColor = { 108, 58, 25 };
	for (int i = 0; i < MAPSIZEY; i++)
	{
		for (int j = 0; j < MAPSIZEX * 2; j += 2)
		{
			if (map[i][j] == (('¦§' & 0xFF00FF) >> 8) && map[i][j+1] == ('¦§' & 0x0000FF))
			{
				GameObject3D* tile = new GameObject3D(tileColor, &m_tile);
				tile->RefPos().x = j / 2 * 9;
				tile->RefPos().z = i * 9;
				tile->RefAngle().z = M_PI;
				m_mapTiles.push_back(tile);
			}
			GameObject3D* tile;
			if (j % 4 == 0)
			{
				tile = new GameObject3D(surface, NULL , &m_tile);
				tile->RefPos().x = j / 2 * 10;
				tile->RefPos().z = i * 10;
			}
			else
			{
				tile = new GameObject3D(tileColor, &m_tile);
				tile->RefPos().x = j / 2 * 10;
				tile->RefPos().z = i * 10;
			}
		

			GameObject3D* tile2 = new GameObject3D(tileColor, &m_tile);
			tile2->RefPos().x = j / 2 * 10;
			tile2->RefPos().z = i * 10;
			tile2->RefPos().y = 40.f;
			tile2->RefAngle().x = M_PI;

			m_mapTiles.push_back(tile);
			m_mapTiles.push_back(tile2);
		}
	}
}

void MapManager::Update()
{
	for (GameObject* gameObject : m_mapTiles)
	{
		gameObject->Update();
	}
}

void MapManager::Render()
{
	for (GameObject* gameObject : m_mapTiles)
	{
		gameObject->Render();
	}
}