#include "MeshManager.h"
#include "Mesh.h"
MeshManager* MeshManager::s_pInst = 0;

void MeshManager::SetMesh(Mesh* mesh, string id)
{
	m_meshMap[id] = mesh;
}

Mesh * MeshManager::GetMesh(string id)
{
	return m_meshMap[id];
}

void MeshManager::Clear()
{
	map<string, Mesh*>::iterator iter = m_meshMap.begin();
	map<string, Mesh*>::iterator iterEnd = m_meshMap.end();
	
	for (; iter != iterEnd; iter++)
		delete iter->second;

	m_meshMap.clear();
}
