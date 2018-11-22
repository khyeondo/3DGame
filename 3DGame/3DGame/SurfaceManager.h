#pragma once

#include <map>
#include <vector>
#include <SDL_image.h>

using namespace std;

class SurfaceManager
{
private:
	static SurfaceManager* s_pInst;
	SurfaceManager() {}

public:
	static SurfaceManager* Instance() {
		if (s_pInst == 0)
			s_pInst = new SurfaceManager();
		return s_pInst;
	}

private:
	map<string, vector<SDL_Surface*>> m_surfaceMap;

public:
	bool load(string fileName, string id);
	vector<SDL_Surface*>* GetSurface(string id);
	void Clear();
};