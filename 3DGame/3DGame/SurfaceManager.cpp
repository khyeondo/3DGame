#include "SurfaceManager.h"

SurfaceManager* SurfaceManager::s_pInst = 0;

bool SurfaceManager::load(string fileName, string id)
{
	SDL_Surface* surface = IMG_Load(fileName.c_str());

	if (surface != 0) {
		m_surfaceMap[id] = surface;
		return true;
	}

	return false;
}

SDL_Surface * SurfaceManager::GetSurface(string id)
{
	return m_surfaceMap[id];
}
