#include "SurfaceManager.h"

SurfaceManager* SurfaceManager::s_pInst = 0;

bool SurfaceManager::load(string fileName, string id)
{
	SDL_Surface* surface = IMG_Load(fileName.c_str());

	if (surface != 0) {
		m_surfaceMap[id].push_back(surface);
		return true;
	}

	return false;
}

vector<SDL_Surface*>* SurfaceManager::GetSurface(string id)
{
	return &m_surfaceMap[id];
}

void SurfaceManager::Clear()
{
	map<string, vector<SDL_Surface*>>::iterator iter = m_surfaceMap.begin();
	map<string, vector<SDL_Surface*>>::iterator iterEnd = m_surfaceMap.end();

	for (; iter != iterEnd; iter++) {
		for (SDL_Surface* surface : iter->second)
		{
			SDL_FreeSurface(surface);
		}
		iter->second.clear();
	}

	m_surfaceMap.clear();
}
