#include "Stage1.h"
#include "GameObject.h"
#include "CameraController.h"
#include "Cube.h"
#include "MapManager.h"
#include "SurfaceManager.h"
#include "MeshManager.h"
#include "Renderer3D.h"
#include "Camera.h"
#include <iostream>

Stage1* Stage1::s_pInstance = 0;
const std::string Stage1::s_Stage1ID = "STAGE1";

void Stage1::init()
{
	for (GameObject* gameObject : m_gameObjects)
	{
		gameObject->Init(this);
	}
}

void Stage1::update()
{
	for (std::vector<GameObject*>::size_type i = 0;
		i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Update(this);
	}
}

void Stage1::render()
{
	for (std::vector<GameObject*>::size_type i = 0;
		i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Render();
	}
}

bool Stage1::onEnter()
{
	SurfaceManager::Instance()->load("Assets/box.png", "box");
	SurfaceManager::Instance()->load("Assets/NormalMap.png", "normalMap");

	Mesh* cube = new Mesh();
	Mesh* plane = new Mesh();
	plane->SetPlane(Vec3(1.f,0.f,1.f), Vec3(2.f, 2.f, 2.f));
	cube->SetCube(Vec3(5.f, 5.f, 5.f), Vec3(10, 10, 10));

	MeshManager::Instance()->SetMesh(plane, "plane");
	MeshManager::Instance()->SetMesh(cube, "cube");

	m_gameObjects.push_back(new CameraController(Renderer3D::Instance()->GetCamera()));
	m_gameObjects.push_back(new MapManager());
	m_gameObjects.push_back(new Cube(SurfaceManager::Instance()->GetSurface("box")->at(0), 
		NULL, MeshManager::Instance()->GetMesh("cube")));

	std::cout << "entering stage1\n";
	return true;
}

bool Stage1::onExit()
{
	SurfaceManager::Instance()->Clear();
	std::cout << "exiting stage1\n";
	return true;
}
