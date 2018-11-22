#pragma once

#include <map>
#include <SDL_image.h>

using namespace std;

class Mesh;

class MeshManager
{
private:
	static MeshManager* s_pInst;
	MeshManager() {}

public:
	static MeshManager* Instance() {
		if (s_pInst == 0)
			s_pInst = new MeshManager();
		return s_pInst;
	}

private:
	map<string, Mesh*> m_meshMap;

public:
	void SetMesh(Mesh* mesh, string id);
	Mesh* GetMesh(string id);
	void Clear();
};