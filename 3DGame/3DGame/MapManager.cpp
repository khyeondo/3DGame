#include "MapManager.h"
#include "GameObject3D.h"
#include "SurfaceManager.h"
#include "Fire.h"
#include "MeshManager.h"

#define MAPSIZEX 20
#define MAPSIZEZ 20
#define MAPHEIGHT 6 

void MapManager::SetTile(Vec3 pos, Vec3 angle, SDL_Surface * surface, SDL_Surface* nomalMap)
{
	GameObject3D* tile = new GameObject3D(surface, nomalMap, &m_tile);
	tile->RefPos().x = pos.x;
	tile->RefPos().y = pos.y;
	tile->RefPos().z = pos.z;
	tile->RefAngle().x = angle.x;
	tile->RefAngle().y = angle.y;
	tile->RefAngle().z = angle.z;
	m_mapTiles.push_back(tile);
}

void MapManager::SetTile(Vec3 pos, Vec3 angle, Color color)
{
	GameObject3D* tile = new GameObject3D(color, &m_tile);
	tile->RefPos().x = pos.x; 
	tile->RefPos().y = pos.y; 
	tile->RefPos().z = pos.z;
	tile->RefAngle().x = angle.x;
	tile->RefAngle().y = angle.y;
	tile->RefAngle().z = angle.z;
	m_mapTiles.push_back(tile);
}

MapManager::MapManager()
{
	m_tag = "MapManager";
}

void MapManager::Init(GameState* pGameState)
{

	/*
	  (0,0)
		 ¦£ ¡æ x+	
		 ¡é 
		 z+
	*/
	wchar_t map[][MAPSIZEX + 1] =
	{
	{ L"¦£¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¨¦¤" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¢Í¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦§¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦©" },
	{ L"¦¦¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦ª¦¥" },

	};

	m_tile.SetPlane(Vec3(10.f, 10.f, 10.f));
	SDL_Surface* surface = SurfaceManager::Instance()->GetSurface("box")->at(0);

	Color tileColor = { 108, 58, 25 };
	for (int i = 0; i < MAPSIZEZ; i++)
	{
		for (int j = 0; j < MAPSIZEX; j++)
		{
			if (map[i][j] == L'¦§')
			{
				for (int k = 0; k < MAPHEIGHT; k++)
				{
					SetTile(Vec3(j * 10, k * 10, i * 10), Vec3(0.f, 0.f, -M_PI / 2.f),tileColor);
				}
			}
			else if (map[i][j] == L'¦©')
			{
				for (int k = 0; k < MAPHEIGHT; k++)
				{
					SetTile(Vec3(j * 10, k * 10, i * 10), Vec3(0.f, 0.f, M_PI / 2.f), tileColor);
				}
			}
			else if (map[i][j] == L'¦¨')
			{
				for (int k = 0; k < MAPHEIGHT; k++)
				{
					SetTile(Vec3(j * 10, k * 10, i * 10), Vec3(M_PI / 2.f, 0.f, 0.f), tileColor);
				}
			}
			else if (map[i][j] == L'¦ª')
			{
				for (int k = 0; k < MAPHEIGHT; k++)
				{
					SetTile(Vec3(j * 10, k * 10, i * 10), Vec3(-M_PI / 2.f, 0.f, 0.f), tileColor);
				}
			}
			else if (map[i][j] == L'¦£')
			{
				for (int k = 0; k < MAPHEIGHT; k++)
				{
					SetTile(Vec3(j * 10, k * 10, i * 10), Vec3(M_PI / 2.f, 0.f, 0.f), tileColor);
					SetTile(Vec3(j * 10, k * 10, i * 10), Vec3(0.f, 0.f, -M_PI / 2.f), tileColor);
				}
			}
			else if (map[i][j] == L'¦¤')
			{
				for (int k = 0; k < MAPHEIGHT; k++)
				{
					SetTile(Vec3(j * 10, k * 10, i * 10), Vec3(M_PI / 2.f, 0.f, 0.f), tileColor);
					SetTile(Vec3(j * 10, k * 10, i * 10), Vec3(0.f, 0.f, M_PI / 2.f), tileColor);
				}
			}
			else if (map[i][j] == L'¦¦')
			{
				for (int k = 0; k < MAPHEIGHT; k++)
				{
					SetTile(Vec3(j * 10, k * 10, i * 10), Vec3(0.f, 0.f, -M_PI / 2.f), tileColor);
					SetTile(Vec3(j * 10, k * 10, i * 10), Vec3(-M_PI / 2.f, 0.f, 0.f), tileColor);
				}
			}
			else if (map[i][j] == L'¦¥')
			{
				for (int k = 0; k < MAPHEIGHT; k++)
				{
					SetTile(Vec3(j * 10, k * 10, i * 10), Vec3(0.f, 0.f, M_PI / 2.f), tileColor);
					SetTile(Vec3(j * 10, k * 10, i * 10), Vec3(-M_PI / 2.f, 0.f, 0.f), tileColor);
				}
			}
			else if (map[i][j] == L'¢Í')
			{
				Fire* pFire = new Fire(SurfaceManager::Instance()->GetSurface("fire")->at(0),
					NULL, MeshManager::Instance()->GetMesh("plane"));
				pFire->RefPos() = Vec3(j * 10, 2.5f, i * 10);

				m_mapTiles.push_back(pFire);
			}

			GameObject3D* tile;
			if (j % 2 == 0)
			{
				tile = new GameObject3D(surface, NULL , &m_tile);
				tile->RefPos().x = j * 10;
				tile->RefPos().z = i * 10;
				tile->RefPos().y -= 5.f;
			}
			else
			{
				tile = new GameObject3D(tileColor, &m_tile);
				tile->RefPos().x = j * 10;
				tile->RefPos().z = i * 10;
				tile->RefPos().y -= 5.f;
			}
		

			GameObject3D* tile2 = new GameObject3D(tileColor, &m_tile);
			tile2->RefPos().x = j * 10;
			tile2->RefPos().z = i * 10;
			tile2->RefPos().y = MAPHEIGHT*9.f;
			tile2->RefAngle().x = M_PI;

			m_mapTiles.push_back(tile);
			m_mapTiles.push_back(tile2);
		}
	}
}

void MapManager::Update(GameState* pGameState)
{
	for (GameObject* gameObject : m_mapTiles)
	{
		gameObject->Update(pGameState);
	}
}

void MapManager::Render()
{
	for (GameObject* gameObject : m_mapTiles)
	{
		gameObject->Render();
	}
}