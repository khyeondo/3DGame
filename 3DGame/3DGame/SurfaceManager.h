#pragma once

#include <map>
#include <SDL_image.h>

using namespace std;

class SurfaceManager
{
private:
	static SurfaceManager* m_pInst;
	SurfaceManager();

public:
	static SurfaceManager* Instance() {
		if (m_pInst == 0)
			m_pInst = new SurfaceManager();
		return m_pInst;
	}

private:
	map<string, SDL_Surface*> m_surfaceMap;

public:
	bool load(string fileName, string id);
	SDL_Surface* GetSurface(string id);

};