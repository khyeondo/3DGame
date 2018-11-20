#include "SurfaceManager.h"

SDL_Surface * SurfaceManager::GetSurface(string id)
{
	return m_surfaceMap[id];
}
